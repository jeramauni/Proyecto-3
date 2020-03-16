#include "GameManager.h"
#include <WindowRenderer.h>
#include <RenderSystem.h>


GameManager::GameManager() {

	windowRenderer = WindowRenderer::getSingleton();
	renderSystem = RenderSystem::getSingleton();


	// Input del gm para cerrar juego
	input = _gmiF->Create();
	input->Init(this);

	//-------------------------- MATERIALS -------------------------------
	//Carga de los materiales que usaremos
	renderSystem->materialGeneration("Mat");
	
	createMenuScene();

	EntityC* _util = new EntityC("penguin");

	/*
	RenderComponent* Rcomp = _rF->Create();
	Rcomp->Init((_util)->_id,
		RenderSystem::getSingleton()->addOgreEntity((_util)->_id));
	(_util)->setNode(Rcomp->getOgreNode());
	(_util)->AddComponent(Rcomp);*/

	gamePlay->push(_util);


	//Añadimos el menu a la pila
	pushScene(menu);

	//----------------------------------INPUT----------------------------------
	// Setup input
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(windowRenderer->getWin());
	mInputManager->addKeyListener(pInput, "PlayerMovement");
	mInputManager->addKeyListener(input, "Escape");
}

GameManager::~GameManager() {
	while (!escenas.empty()) {
		escenas.pop();
	}
}

bool GameManager::update() {
	//------Input------
	mInputManager->capture();

	if (input->_state) { //La cosa es que los componentes le digan a su entidad lo que hacer.
		windowRenderer->windowClosed();
		return false;
	}

	//------Renderizado------
	windowRenderer->renderFrame(0);

	return true;
}

void GameManager::pushScene(Scene* newScene) {
	renderSystem->clearScene();
	escenas.push(newScene);
	//escenas.top()->render();
}

void GameManager::popScene() {
	renderSystem->clearScene();
	escenas.pop();
	//escenas.top()->render();
}

void GameManager::createMenuScene()
{
	renderSystem->addCamera();
	//--------------------------- LIGHT -----------------------------
	//Creacion de la luz en la escena
	renderSystem->setAmbientLight(Ogre::ColourValue(0.2f, 0.0f, 0.2f, 1.0f));
	//--------------------------- ENTIDADES ---------------------------
	EntityC* _util = new EntityC("ninja");
	pInput = _piF->Create();
	pInput->Init(_util);

	renderSystem->addOgreEntity("ninja");

	renderSystem->squareGeneration();

	/*RenderComponent* Rcomp = _rF->Create();
	Rcomp->Init((_util)->_id,
		renderSystem->addOgreEntity((_util)->_id));
	(_util)->setNode(Rcomp->getOgreNode());
	(_util)->AddComponent(Rcomp);*/

	menu->push(_util);
}
