#include "WEManager.h"

#include <iostream>
//Entity
#include <EntityC.h>
//Factories
#include <ComponentFactory.h>
// Renderizado
#include <WindowRenderer.h>
#include <RenderSystem.h>
// PhysicsManager
#include <PhysicsEngine.h>
// DataManager
#include<DataManager.h>
// InputManager
#include <InputManager.h>

//Escena
#include "Scene.h"
#include <Messages_defs.h>
	  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 ////////////////////////////////////////////     SOLO PARA PRUEBAS     ///////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <WEInput.h>
	
	//Jugador
Container* player;
btVector3 velocity = btVector3(0,0,0);
	  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 ////////////////////////////////////////////     SOLO PARA PRUEBAS     ///////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WEManager::WEManager() {
	py = nullptr;
	dM = nullptr;
	windowRenderer = nullptr;
	renderSystem = nullptr;
	mInputManager = nullptr;
	input = nullptr;
	end = false;
	windowRenderer = nullptr;
	renderSystem = nullptr;
}

WEManager::~WEManager() {
	while (!escenas.empty()) {
		escenas.pop();
	}
}

void WEManager::Init() {
	//DataManager
	dM = new DataManager();
	dM->setWEM(this);

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

// Genera la escena leyendo del archivo de datos
void WEManager::generateScene(std::string sceneName) {
	//Creamos la escena
	Scene *mScene = new Scene(sceneName, this);
	renderSystem->createScene(mScene->getID());

	//----------COSAS DE CAMARA--------------
	//Sin vp no se ve nada, tenga color o no (MainCam es la camara creada por defecto en
	//las escenas, se pueden añadir mas)
	renderSystem->addVpToCam("MainCam", Ogre::ColourValue(0.2, 0, 0.2, 0.8));

	//Por si queremos mover una camara
	//renderSystem->moveCam("MainCam", 0, 0, 0);
	//Por si queremos que una camara mire a otro lado
	//renderSystem->camLookAt("MainCam", Ogre::Vector3(0, 0, 0));

	//--------------------------- LIGHT -----------------------------
	//Creacion de la luz en la escena, la luz se le aplica a las entidades
	renderSystem->setAmbientLight(Ogre::ColourValue(0.0f, 1.0f, 0.0f, 1.0f));




	//------------------------------------------------------------------
	//----------------------------ENTIDADES-----------------------------
	//------------------------------------------------------------------
	//Leemos las entidades del archivo de datos
	std::vector<Container*> ent = dM->Load(sceneName, "entities.json", false);

	// Recorremos las entidades leidas para relacionarlas con los managers que necesiten
	// y darles las caracteristicas que las haga falta
	for (int i = 0; i < ent.size(); i++) {
	  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 ////////////////////////////////////////////     SOLO PARA PRUEBAS     ///////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		WEInput* weinput = new WEInput(ent[0]);
		mInputManager->addKeyListener(weinput->getListener(), "ninja");
		ent[0]->AddComponent(weinput);
		player = ent[0];
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////     SOLO PARA PRUEBAS     ///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Creamos el nodo de ogre a partir de la mesh del renderComponent
		if (ent[i]->hasComponent("Render")) {
			ent[i]->setNode(renderSystem->addOgreEntity(ent[i]->GetEntityName(), static_cast<RenderComponent*>(ent[i]->getComponent("Render"))->getMeshName()));
		}

		// Cambiamos la posicion del nodo de ogre a partir del componente Transform
		if (ent[i]->hasComponent("Transform")) {
			Component* tcomp = ent[i]->getComponent("Transform");
			ent[i]->setPos(*static_cast<TransformComponent*>(tcomp)->GetPosition());
		}

		// ToDo:: 
		// si tiene fisicos a las fisicas
		if (ent[i]->hasComponent("Physics")) {
			PhysicsComponent* p = static_cast<PhysicsComponent*>(ent[i]->getComponent("Physics"));
			p->SetID(py->basicMesh(ent[i]->getNode(), p->GetScale(), p->HaveGravity()));
		}
		// si tiene input al controlador de input

		// En entidad separar por tipos de componentes 
		//

		// Añadimos la entidad a la escena
		mScene->addEntity(ent[i]);
	}

	pushScene(mScene);
}

void WEManager::close() { end = true; }

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

void WEManager::pushScene(Scene* newScene) {
	renderSystem->setRenderingScene(newScene->getID());
	escenas.push(newScene);
}

void WEManager::popScene() {
	escenas.pop();
	renderSystem->setRenderingScene(escenas.top()->getID());
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