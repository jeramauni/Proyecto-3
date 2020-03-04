#include "GameManager.h"

#include "RenderComponent.h"
#include "EntityC.h"
#include "RenderUtilities.h"
#include "InitOgre.h"

GameManager::GameManager(OgreEasy::OgreApp * oa) {
	ogreApp = oa;

	//----------------------------------INPUT----------------------------------
	okc = new OneKeyComponent();

	// Setup input
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(ogreApp->getWindow());
	mInputManager->addKeyListener(okc, "Escape");

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

	changeScene(menu);
}

GameManager::~GameManager() {
	escenas.empty();
}

bool GameManager::update() {
	//------Input------
	mInputManager->capture();
	if (okc->state) ogreApp->turnOff(); //La cosa es que los componentes le digan a su entidad lo que hacer.
	else if (okc->changeState) {
		okc->changeState = false;
		if (escenas.top() == menu) {
			changeScene(gamePlay);
		}
		else {
			changeScene(menu);
		}
	}

	return ogreApp->RenderLoop();
}
void GameManager::changeScene(Scene *newScene) {
	ogreApp->SceneCleaner();
	escenas.push(newScene);
	escenas.top()->render(ogreApp);
}