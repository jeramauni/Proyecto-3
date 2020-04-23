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

WEManager::WEManager()
{
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

	// Añadimos al InputMng el InputKeyListener k vayamos a usar para la gestion de las teclas
	//input = new InputListener(this);
	//mInputManager->addKeyListener(input, "input");
	//mInputManager->addKeyListener(this, "input");

	//-------------------------- MATERIALS -------------------------------
	//Carga de los materiales que usaremos
	renderSystem->materialGeneration(" Mat");
}

// Genera la escena leyendo del archivo de datos
void WEManager::generateScene(std::string sceneName) {
	//Creamos la escena
	Scene *mScene = new Scene(sceneName);
	renderSystem->createScene(mScene->getID());

	//Leemos las entidades del archivo de datos
	std::vector<Container*> ent = dM->Load(sceneName, "entities.json");

	for (int i = 0; i < ent.size(); i++) {
		// Creamos el nodo de ogre a partir de la mesh del renderComponent
		if (ent[i]->hasComponent("Render")) {
			ent[i]->setNode(renderSystem->addOgreEntity(static_cast<RenderComponent*>(ent[i]->getComponent("Render"))->getMeshName()));
		}

		// Cambiamos la posicion del nodo de ogre a partir del componente Transform
		if (ent[i]->hasComponent("Transform")) {
			Component* tcomp = ent[i]->getComponent("Transform");
			ent[i]->setPos(*static_cast<TransformComponent*>(tcomp)->GetPosition());
		}

		// ToDo:: 
		// si tiene fisicos a las fisicas
		//
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
	//escenas.top()->update();

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
	//addObserver(newScene);
}

void WEManager::popScene() {
	escenas.pop();
	renderSystem->setRenderingScene(escenas.top()->getID());
}

//---------------------------------------Mensajes--------------------------------------
// Para enviar los mensajes
void WEManager::send(const void* senderObj, const msg::Message& msg) {
	escenas.top()->receive(senderObj, msg);
	//if(this != senderObj) receive(senderObj, msg);
	/*for (Observer* o : observers_) {
		if (senderObj != o) {
			if (msg.destination_ == msg::Broadcast // we send to everyone, even to the one from whom we received the message!
				|| msg.destination_ == o->getId()) {
				o->receive(senderObj, msg);
			}
		}
	}*/
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