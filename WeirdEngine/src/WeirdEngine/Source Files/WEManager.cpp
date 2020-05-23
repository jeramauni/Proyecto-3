#include "WEManager.h"

#include <iostream>
//Entity
#include <Container.h>

//Factories
#include <ComponentFactory.h>
// Renderizado
#include <WindowRenderer.h>
#include <RenderSystem.h>
#include <CEGUI/CEGUI.h>
// PhysicsManager
#include <PhysicsEngine.h>
// DataManager
#include <DataManager.h>
// InputManager
#include <InputManager.h>
// AudioManager
#include <AudioManager.h>

//Escena
#include "Scene.h"
#include "Messages_defs.h"

//Utilities
#include "Utilities\Vector3.h"
#include "Utilities\Vector4.h"

extern FactoriesGestor* factoriesGestor = FactoriesGestor::getInstance();

//------------------Quitar estoo-------------------------
//Componentes
#include "RenderComponent.h"
CREATE_REGISTER(Render);
//------------------Quitar estoo-------------------------

bool WEManager::end = false;

// Constructora
WEManager::WEManager() {
	py = nullptr;
	dM = nullptr;
	windowRenderer = nullptr;
	renderSystem = nullptr;
	mInputManager = nullptr;
	audioManager = nullptr;
	
	end = false;
}

//Destructora
WEManager::~WEManager() {
	while (!escenas.empty()) {
		delete escenas.top();
		escenas.pop();
	}

	delete dM;
	delete py;
	delete mInputManager;
}

/*
WEManager* WEManager::getInstance() {
	if (_instance == nullptr) {
		_instance = new WEManager();
		_instance->Init();
	}
	
	return _instance;
}
*/

//Inicializacion
void WEManager::Init() {
	//DataManager
	dM = new DataManager();

	//Inicializar physics
	py = new PhysicsEngine();
	py->initObjects();


	//Sistema de render
	if (RenderSystem::initSingleton()) {
		renderSystem = RenderSystem::getSingleton();
		//Ogre window
		windowRenderer = WindowRenderer::getSingleton();
	}

	//Sistema de audio
	if (AudioManager::initSingleton()) {
		audioManager = AudioManager::getSingleton();
	}

	audioManager->createSound("audio1", "menumusic.wav");
	audioManager->play("audio1");

	//----------------------------------INPUT----------------------------------
	// Setup input
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(windowRenderer->getWin());
	mInputManager->addMouseListener(renderSystem, "renderListener");

	//-------------------------- MATERIALS -------------------------------
	//Carga de los materiales que usaremos
	renderSystem->materialGeneration(" Mat");
}

//Update
bool WEManager::update() {
	//------Input------
	mInputManager->capture();

	//Update
	escenas.top()->update(0);

	// Fisicas
	py->physicsLoop();

	//------Renderizado------
	renderSystem->draw(0);
	

	//Cerrar ventana -> esto lo tiene que hacer el juego
	if (end) {
		windowRenderer->windowClosed();
		return false;
	}

	return true;
}

//const CEGUI::EventArgs&
void WEManager::close() { 
	//std::cout << "Cerrando!\n";
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
	addVpToCam("MainCam", Vector4{0.2, 0.0, 0.2, 0.8});

	//Colocamos la camara
	moveCam("MainCam", { 250, 400, -700 });
	camLookAt("MainCam", { 250, 0, 0 });
	rotateCam("MainCam", { 0, 0, 180, 1 });

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

void WEManager::createButton(std::string type, std::string widgetName, std::string text, Vector4 Perc, Vector4 Pixels) {
	renderSystem->createButton(type, widgetName, text, Perc, Pixels);
}

void WEManager::addEventToButton(std::string name, CEGUI::SubscriberSlot f) {
	renderSystem->addEventToButton(name, f);
}

void WEManager::loadLayout(std::string layoutName) {
	renderSystem->setLayout(layoutName);
}

void WEManager::setGUIVisible(bool b) {
	renderSystem->setGUIVisible(b);
}

// Pila de escenas
void WEManager::pushScene(Scene* newScene) {
	renderSystem->setRenderingScene(newScene->getID());
	escenas.push(newScene);
}

void WEManager::popScene() {
	renderSystem->clearScene();
	escenas.pop();
	renderSystem->setRenderingScene(escenas.top()->getID());
}

//---------------------------CONTROL DE CAMARA-----------------------------------------
void WEManager::addCameraToScene(std::string cameraName) {
	renderSystem->addCamera(cameraName);
}

void WEManager::addVpToCam(std::string cameraName, Vector4 colors) {
	renderSystem->addVpToCam(cameraName, Ogre::ColourValue(colors.x, colors.y, colors.z, colors.w));
}

void WEManager::moveCam(std::string camName, Vector3 p) {
	renderSystem->moveCam(camName, p.x, p.y, p.z);
}

void WEManager::camLookAt(std::string camName, Vector3 p) {
	renderSystem->camLookAt(camName, Ogre::Vector3(p.x, p.y, p.z));
}

void WEManager::rotateCam(std::string camName, Vector4 quat) {
	renderSystem->rotateCam(camName, Ogre::Quaternion(quat.w, quat.x, quat.y, quat.z));
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
		if (escenas.size() > 1) popScene();
		else end = true;
		break;
	default:
		break;
	}
}

//Privates
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
		if (factoriesGestor->getFactories().find(prefabs[0].at("components")[j].at("id")) != factoriesGestor->getFactories().end()) {
			scene->AddComponent(factoriesGestor->getFactories().at(prefabs[0].at("components")[j].at("id"))->Create(scene));
			//Para cada parametro del componente excluyendo el id

			for (auto x = prefabs[0].at("components")[j].begin(); x != prefabs[0].at("components")[j].end(); x++)
			{
				param.insert(std::pair<std::string, std::string>(x.key(), x.value()));
			}
			scene->getComponent(prefabs[0].at("components")[j].at("id"))->Init(param);
		}
		else {
			std::cout << "WARNING!! -------> " /*+ std::string(prefabs[0].at("components")[j].at("id")) +*/ " no esta declarado en las factorias\n";
		}
	}
}

void WEManager::setCeguiLayout(std::string layoutName) {
	renderSystem->setLayout(layoutName);
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
			if (factoriesGestor->getFactories().find(prefabs[i].at("components")[j].at("id")) != factoriesGestor->getFactories().end()) {
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
			else {
				std::cout << "WARNING!! -------> " /*+ std::string(prefabs[i].at("components")[j].at("id")) +*/ " no esta declarado en las factorias\n";
			}
		}

		if (true) {
			std::cout << "Entity " << entity_name << " successfully created";
			//Vector3* v = static_cast<TransformComponent*>(e->getComponent("Transform"))->GetPosition();
			//std::cout << v->x << ", " << v->y << ", " << v->z << " }" << '\n';
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