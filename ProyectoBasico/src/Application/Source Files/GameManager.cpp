#include "GameManager.h"

GameManager::GameManager(OgreEasy::OgreApp * oa) {
	ogreApp = oa;

	// Input del gm para cerrar juego
	input = _gmiF->Create();
	input->Init(this);

	//--------------------------- LIGHT -----------------------------
	//Creacion de la luz en la escena
	ogreApp->lightGeneration();

	//-------------------------- MATERIALS -------------------------------
	//Carga de los materiales que usaremos
	ogreApp->materialGeneration(" Mat");

	//--------------------------- SCENES ---------------------------
	EntityC* _util = new EntityC("ninja");
	pInput = _piF->Create();
	pInput->Init(_util);

	menu->push(_util);

	_util = new EntityC("penguin");
	gamePlay->push(_util);

	//Añadimos el menu a la pila
	pushScene(menu);

	//----------------------------------INPUT----------------------------------
	// Setup input
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(ogreApp->getWindow());
	mInputManager->addKeyListener(pInput->getListener(), "PlayerMovement");
	mInputManager->addKeyListener(input->getListener(), "Escape");
}

GameManager::~GameManager() {
	while (!escenas.empty()) {
		escenas.pop();
	}
}

bool GameManager::update() {
	//------Input------
	mInputManager->capture();
	if (input->_state) ogreApp->turnOff(); //La cosa es que los componentes le digan a su entidad lo que hacer.

	return ogreApp->RenderLoop();
}

void GameManager::pushScene(Scene* newScene) {
	ogreApp->SceneCleaner();
	escenas.push(newScene);
	escenas.top()->render(ogreApp);
}

void GameManager::popScene() {
	ogreApp->SceneCleaner();
	escenas.pop();
	escenas.top()->render(ogreApp);
}