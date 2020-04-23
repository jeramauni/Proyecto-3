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
#include <InputKeyListener.h>

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
	// ToDo
	// Editar el inputKeyListener para que pueda mandar mensajes
	// Añadimos al InputMng el InputKeyListener k vayamos a usar para la gestion de las teclas
	input = new InputKeyListener(this);
	mInputManager->addKeyListener(input, "input");
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
	std::vector<EntityC*> ent = dM->Load(sceneName, "entities.json", true);


	////--------------TEMP
	/*ent[0]->setNode(renderSystem->addOgreEntity(static_cast<RenderComponent*>(ent[0]->getComponent("Render"))->getMeshName()));
	Component* tcomp = ent[0]->getComponent("Transform");
	ent[0]->setPos(*static_cast<TransformComponent*>(tcomp)->GetPosition());
	
	mScene->addEntity(ent[0]);*/
	////---------------------

	for (int i = 0; i < ent.size(); i++) {
		// ToDo:: 
		// Mirar los componentes de las entidades y añadimos 
		// con el transform generamos el nodo
		
		// Si le guardamos el nombre del "mesh" en la info de la entidad
		// eso es lo que habra que pasarle a addOgreEntity
		if (ent[i]->ComponentTracker("Render")) {
			ent[i]->setNode(renderSystem->addOgreEntity(static_cast<RenderComponent*>(ent[i]->getComponent("Render"))->getMeshName()));
		}
		//ent[i]->setNode(renderSystem->addOgreEntity(ent[i]->_id));
		//Component *tcomp = ent[i]->getComponent("transform");
		//ent[i]->setPos(static_cast<TransformComponent*>(tcomp)->GetPosition());
		if (ent[i]->ComponentTracker("Transform")) {
			Component* tcomp = ent[i]->getComponent("Transform");
			ent[i]->setPos(*static_cast<TransformComponent*>(tcomp)->GetPosition());
		}

		// si tiene fisicos a las fisicas
		if (ent[i]->ComponentTracker("Physics")) {
			//py->basicMesh(ent[i]->getNode());
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
}

void WEManager::popScene() {
	escenas.pop();
	renderSystem->setRenderingScene(escenas.top()->getID());
}

//---------------------------------------Input--------------------------------------
// Componente para las entidades que escuchan del input
void WEManager::send(const void* senderObj, const msg::Message& msg) {
	escenas.top()->send(senderObj, msg);
	receive(senderObj, msg);
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

// La idea es que el WEManager sea un KeyListener y mande los msg correspondientes pero no funciona :(
bool WEManager::keyPressed(const OIS::KeyEvent& ke) {
	switch (ke.key) {
	case OIS::KC_W:
		std::cout << "Moverse W!\n";
		break;
	case OIS::KC_A:
		std::cout << "Moverse A!\n";
		break;
	case OIS::KC_S:
		std::cout << "Moverse S!\n";
		break;
	case OIS::KC_D:
		std::cout << "Moverse D!\n";
		break;
	case OIS::KC_ESCAPE:
		this->send(this, msg::Close_Win(msg::WEManager, msg::Broadcast));
		break;
	case OIS::KC_SPACE:
		this->send(this, msg::Prueba(msg::WEManager, msg::Broadcast));
		break;
	default:
		break;
	}

	return true;
}

bool WEManager::keyReleased(const OIS::KeyEvent& ke) {
	return false;
}
