#include "GameManager.h"

// Renderizado
#include <WindowRenderer.h>
#include <RenderSystem.h>
// PhysicsManager
#include <PhysicsEngine.h>
// InputManager
#include <InputManager.h>
#include "InputListener.h"
// DataManager
#include<DataManager.h>

//Mensajes
#include "Messages_defs.h"

GameManager::GameManager() {}

GameManager::~GameManager() {
	while (!escenas.empty()) {
		escenas.pop();
	}
}

void GameManager::Init() {
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


	//COSAS DE CADA JUEGO
	////-----*INPUT*-------------
	// Este input se crearia en cada juego con las teclas especificas que se van a usar en el juego, y se usaria para que
	// cuando el input detecta entrada de una de las teclas, el gm mande un mensaje broadcast a todas las entidades 
	// de la escena, afectadas por ese emnsaje, tambien se lo mandara el mensaje a si mismo (al gm) para actuar en funcion
	// al mensaje si tiene que hacerlo
	iList = new InputListener(this);
	this->addListener(iList, "JuegosKeys");

	/// Esto va en otro ladu
	generateScene("nivel1.json");
}

// Genera la escena leyendo del archivo de datos
void GameManager::generateScene(std::string sceneName) {
	//Creamos la escena
	Scene *mScene = new Scene(sceneName);
	renderSystem->createScene(mScene->getID());

	//Leemos las entidades del archivo de datos
	std::vector<EntityC*> ent = dM->Load("map.txt", "entities.json");

	for (int i = 0; i < ent.size(); i++) { //Muy feo esto
		// ToDo:: 
		// Mirar los componentes de las entidades y añadimos 
		// con el transform generamos el nodo
		ent[i]->setNode(renderSystem->addOgreEntity(ent[i]->_id));
		Component *tcomp = ent[i]->getComponent("transform");
		ent[i]->setPos(static_cast<TransformComponent*>(tcomp)->GetPosition());
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

bool GameManager::update() {
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

	//Cerrar ventana
	if (end) {
		windowRenderer->windowClosed();
		return false;
	}

	return true;
}

void GameManager::addListener(InputListener *iL, Ogre::String name) {
	mInputManager->addKeyListener(iL, name);
}

void GameManager::pushScene(Scene* newScene) {
	renderSystem->setRenderingScene(newScene->getID());
	escenas.push(newScene);
}

void GameManager::popScene() {
	escenas.pop();
	renderSystem->setRenderingScene(escenas.top()->getID());
}

void GameManager::send(const void* senderObj, const msg::Message& msg) {
	escenas.top()->send(senderObj, msg);
	receive(senderObj, msg);
}

void GameManager::receive(const void* senderObj, const msg::Message& msg) {
	switch (msg.type_)
	{
	case msg::CLOSE_WIN:
		end = true;
		break;
	default:
		break;
	}
}