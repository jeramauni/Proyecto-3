#include "GameManager.h"

#include "RenderComponent.h"
#include "EntityC.h"
#include "RenderUtilities.h"
#include "InitOgre.h"

GameManager::GameManager(OgreEasy::OgreApp * oa) {
	ogreApp = oa;

	//----------------------------------INPUT----------------------------------
	input = new GmInputComponent(this);

	// Setup input
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(ogreApp->getWindow());
	mInputManager->addKeyListener(input, "Escape");

	//--------------------------- LIGHT -----------------------------
	//Creacion de la luz en la escena
	ogreApp->lightGeneration();

	//-------------------------- MATERIALS -------------------------------
	//Carga de los materiales que usaremos
	ogreApp->materialGeneration(" Mat");

	//--------------------------- SCENES ---------------------------
	EntityC* _util = new EntityC("ninja");
	menu->push(_util);

	_util = new EntityC("penguin");
	gamePlay->push(_util);

	//Añadimos el menu a la pila
	pushScene(menu);
	//escenas.push(gamePlay);
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

void GameManager::changeScene(Scene *newScene) {
	ogreApp->SceneCleaner();
	escenas.push(newScene);
	escenas.top()->render(ogreApp);
}