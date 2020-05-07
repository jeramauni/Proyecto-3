#include "WEManager.h"

#include <iostream>
//Entity
#include <Container.h>
#include "Vector3.h"

//Factories
#include <ComponentFactory.h>
// Renderizado
#include <WindowRenderer.h>
#include <RenderSystem.h>
// PhysicsManager
#include <PhysicsEngine.h>
// DataManager
#include <DataManager.h>
// InputManager
#include <InputManager.h>

//Escena
#include "Scene.h"
#include <Messages_defs.h>

//Componentes
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"

extern FactoriesGestor* factoriesGestor = FactoriesGestor::getInstance();

CREATE_REGISTER(Render);

// Constructora
WEManager::WEManager() {
	py = nullptr;
	dM = nullptr;
	windowRenderer = nullptr;
	renderSystem = nullptr;
	mInputManager = nullptr;
	windowRenderer = nullptr;
	renderSystem = nullptr;
	
	end = false;
}

//Destructora
WEManager::~WEManager() {
	while (!escenas.empty()) {
		escenas.pop();
	}
}

//Inicializacion
void WEManager::Init() {
	//DataManager
	dM = new DataManager();

	//Inicializar physics
	py = new PhysicsEngine();
	py->initObjects();

	// Ogre
	if (WindowRenderer::initSingleton())
		windowRenderer = WindowRenderer::getSingleton();

	//Sistema de render
	if (RenderSystem::initSingleton()) {
		renderSystem = RenderSystem::getSingleton();
	}

	//----------------------------------INPUT----------------------------------
	// Setup input
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(windowRenderer->getWin());

	//-------------------------- MATERIALS -------------------------------
	//Carga de los materiales que usaremos
	renderSystem->materialGeneration(" Mat");
}

//Update
bool WEManager::update() {
	//------Input------
	mInputManager->capture();
	
	// Fisicas
	py->physicsLoop();

	//Update
	//escenas.top()->update(0);

	//------Renderizado------
	windowRenderer->renderFrame(0);

	//------Ventana------
	windowRenderer->handleEvents();

	//Cerrar ventana -> esto lo tiene que hacer el juego
	if (end) {
		windowRenderer->windowClosed();
		return false;
	}

	return true;
}

void WEManager::close() { 
	end = true; 
}

//---------------------------------Escena----------------------------------------------------
void WEManager::generateScene(std::string sceneName, std::string entidades) {
	// Creamos la escena
	Scene* mScene = new Scene(sceneName, this);
	renderSystem->createScene(mScene->getID());

	//----------COSAS DE CAMARA--------------
	// Sin vp no se ve nada, tenga color o no (MainCam es la camara creada por defecto en
	// las escenas, se pueden añadir mas)
	addVpToCam("MainCam", 0.2, 0, 0.2, 0.8);

	//--------------------------- LIGHT -----------------------------
	// Creacion de la luz en la escena, la luz se le aplica a las entidades
	setLight(1.0f, 1.0f, 1.0f, 1.0f); //Luz blanca

	// Leemos las entidades y las guardamos para generarlas
	std::vector<std::vector<std::string>> map = dM->ReadMap(sceneName + ".txt");
	json prefabs = dM->ReadJson(entidades + ".json");
	prefabs = prefabs.at(prefabs.begin().key());

	// Añadimos los componentes a la escena
	addComponentsToScene(mScene, prefabs);

	// Generamos las entidades en la escena
	generateEntities(mScene, map, prefabs);

	// Añadimos la escena a la pila de escenas
	pushScene(mScene);
}

void WEManager::generateEntities(Scene* scene, std::vector<std::vector<std::string>> map, json prefabs) {
	// Recorremos el mapa generando las entidades
	int n = std::stoi(map[0][0]);		//Number of entities on legend
	int aux = n + 1;					//row aux variable
	int ct = 0, cct = 0;				//row counter 
	std::map<int, std::string> legend;	//Map of entitie types on map (id on map - name on prefabs file)
	char xyz[3];						//Axis representation on map (Columns x Rows / Between layers) (x-y-z)
	int r, c;							//Mapsize (Row - columns)
	float s;							//Size between tiles
	int layer = 0;
	//Entity processing
	float slyr = 0.0;						//Size between layers
	int id = -1;						//id of entity to process
	//Position processing
	Vector3 currentpos_ = { 0.0f, 0.0f, 0.0f };
	//Legend
	for (std::size_t i = 1; i <= n; i++)
	{
		legend[std::stoi(map[i][0])] = map[i][1];
	}
	//Axis representation
	for (std::size_t i = 0; i < 3; i++)
		xyz[i] = map[aux][i].back(); aux++;
	//Size between tiles
	s = std::stof(map[aux][0]);	aux++;
	//Mapsize (columns - rows)
	c = std::stoi(map[aux][0]);
	r = std::stoi(map[aux][1]); aux++;

	int nEnt = 0;

	//Layers
	for (auto row = map.begin() + aux++; row != map.end(); row++)
	{
		ct++;
		for (auto column = row->begin(); column != row->end(); column++)
		{
			if (ct > r)	//If we are at the row between layers we get the distance between layers
			{
				layer++;
				slyr += std::stof(*column);
				ct = 0;

			}
			else		//If not we get the next id..
			{
				id = std::stoi(*column);
				if (id != -1)
				{
					//...set the next position..
					currentpos_ = setProperPosition(ct - 1, cct, layer, xyz, s, slyr);
					//..and create the proper entity
					scene->addEntity(CreateEntity(legend[id], prefabs, nEnt, currentpos_));
				}
			}
			cct++;
			nEnt++;
		}
		cct = 0;
		std::cout << '\n';
	}
}

void WEManager::addComponentsToScene(Scene* scene, json prefabs) {
	std::unordered_map<std::string, std::string> param;
	int size_ = prefabs[0].at("components").size();
	//Para cada componente en la lista de componentes
	for (std::size_t j = 0; j < size_; j++)
	{
		scene->AddComponent(factoriesGestor->getFactories().at(prefabs[0].at("components")[j].at("id"))->Create(scene));
		//Para cada parametro del componente excluyendo el id

		for (auto x = prefabs[0].at("components")[j].begin(); x != prefabs[0].at("components")[j].end(); x++)
		{
			param.insert(std::pair<std::string, std::string>(x.key(), x.value()));
		}
		scene->getComponent(prefabs[0].at("components")[j].at("id"))->Init(param);
	}
}


Container* WEManager::CreateEntity(std::string& id, json prefabs, uint32_t n_entities, Vector3 position_) {
	uint32_t i = 1;
	//Busqueda de id en el archivo de prefabs
	while (i < prefabs.size() && prefabs[i].at("id") != id) {
		i++;
	}
	//Si no lo encuentra lo notifica y devuelve nullptr
	if (i >= prefabs.size())
	{
		std::cerr << "Entity " << id << " not found on prefabs file!" << '\n';
		return nullptr;
	}
	//Si lo encuentra crea y devuelve la entidad 
	else
	{
		//Hay que hacer la lectura de id's de componentes
		std::string entity_name = id + "_" + std::to_string(n_entities);
		Container* e = new Container(entity_name, this);

		std::unordered_map<std::string, std::string> param;
		int size_ = prefabs[i].at("components").size();
		//Para cada componente en la lista de componentes
		for (std::size_t j = 0; j < size_; j++)
		{
			e->AddComponent(factoriesGestor->getFactories().at(prefabs[i].at("components")[j].at("id"))->Create(e));
			//Para cada parametro del componente excluyendo el id

			for (auto x = prefabs[i].at("components")[j].begin(); x != prefabs[i].at("components")[j].end(); x++)
			{
				param.insert(std::pair<std::string, std::string>(x.key(), x.value()));
			}

			if (prefabs[i].at("components")[j].at("id") == "Transform") {
				if (param.find("positionT") != param.end()) {
					std::string p = std::to_string(position_.x) + '/' + std::to_string(position_.y) + '/' + std::to_string(position_.z);
					param.at("positionT") = p;
				}
			}
			e->getComponent(prefabs[i].at("components")[j].at("id"))->Init(param);
		}

		//e->setPos(position_);

		// si tiene fisicos a las fisicas
		if (e->hasComponent("Physics")) {
			//PhysicsComponent* p = static_cast<PhysicsComponent*>(e->getComponent("Physics"));
			//p->SetID(py->basicMesh(e->getNode(), p->GetScale(), p->HaveGravity()));
		}

		if (true) {
			std::cout << "Entity " << entity_name << " successfully created at position: { ";
			Vector3* v = static_cast<TransformComponent*>(e->getComponent("Transform"))->GetPosition();
			std::cout << v->x << ", " << v->y << ", " << v->z << " }" << '\n';
		}
		
		return e;
	}
}

Vector3 WEManager::setProperPosition(int row, int column, int layer, char xyz[3], float size_tiles, float size_layer) {
	Vector3 propperPos = { 0.0f, 0.0f, 0.0f };
	float x = 0.0, y = 0.0, z = 0.0;

	//Column value
	if (xyz[0] == 'x')		x = column * size_tiles;
	else if (xyz[0] == 'y')	y = column * size_tiles;
	else if (xyz[0] == 'z')	z = column * size_tiles;
	//Row value
	if (xyz[1] == 'x')		x = row * size_tiles;
	else if (xyz[1] == 'y')	y = row * size_tiles;
	else if (xyz[1] == 'z')	z = row * size_tiles;
	//Layer value
	if (xyz[2] == 'x')		x = size_layer;
	else if (xyz[2] == 'y')	y = size_layer;
	else if (xyz[2] == 'z')	z = size_layer;

	propperPos.set(x, y, z);
	return propperPos;
}

// Pila de escenas
void WEManager::pushScene(Scene* newScene) {
	renderSystem->setRenderingScene(newScene->getID());
	escenas.push(newScene);
}

void WEManager::popScene() {
	escenas.pop();
	renderSystem->setRenderingScene(escenas.top()->getID());
}

//---------------------------CONTROL DE CAMARA-----------------------------------------
void WEManager::addCameraToScene(std::string cameraName) {
	renderSystem->addCamera(cameraName);
}

void WEManager::addVpToCam(std::string cameraName, float r, float g, float b, float a) {
	renderSystem->addVpToCam(cameraName, Ogre::ColourValue(r, g, b, a));
}

void WEManager::moveCam(std::string camName, float x, float y, float z) {
	renderSystem->moveCam(camName, x, y, z);
}

void WEManager::camLookAt(std::string camName, float x, float y, float z) {
	renderSystem->camLookAt(camName, Ogre::Vector3(x, y, z));
}

void WEManager::rotateCam(std::string camName, float w, float x, float y, float z) {
	renderSystem->rotateCam(camName, Ogre::Quaternion(w, x, y, z));
}


//----------------------Input-------------------
void WEManager::addKeyListener(InputKeyListener* iL, std::string name) {
	mInputManager->addKeyListener(iL, name);
}

void WEManager::addMouseListener(InputMouseListener* iL, std::string name) {
	mInputManager->addMouseListener(iL, name);
}

//Luz
void WEManager::setLight(float r, float g, float b, float a) {
	renderSystem->setAmbientLight(Ogre::ColourValue(r, g, b, a));
}

//---------------------------------------Mensajes--------------------------------------
// Para enviar los mensajes
void WEManager::send(const void* senderObj, const msg::Message& msg) {
	this->receive(senderObj, msg);
	escenas.top()->receive(senderObj, msg);
}


void WEManager::receive(const void* senderObj, const msg::Message& msg) {
	switch (msg.type_) {
	case msg::CLOSE_WIN:
		end = true;
		break;
	default:
		break;
	}
}