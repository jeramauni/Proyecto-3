#include "GameManager.h"
#include <WindowRenderer.h>
#include <RenderSystem.h>

GameManager::GameManager() {
	//Inicializar physics
	py = new PhysicsEngine();
	py->initObjects();
	// Input del gm para cerrar juego
	input = _gmiF->Create();
	input->Init(this);

	if (WindowRenderer::initSingleton())
		windowRenderer = WindowRenderer::getSingleton();

	if (RenderSystem::initSingleton()) {
		renderSystem = RenderSystem::getSingleton();
	}

	//--------------------------- LIGHT -----------------------------
	//Creacion de la luz en la escena

	//-------------------------- MATERIALS -------------------------------
	//Carga de los materiales que usaremos
	renderSystem->materialGeneration(" Mat");

	//--------------------------- SCENES ---------------------------
	createGameScene();

	//Añadimos el menu a la pila
	createMenuScene();
	pushScene(menu);

	//----------------------------------INPUT----------------------------------
	// Setup input
	mInputManager = InputManager::getSingletonPtr();
	mInputManager->initialise(windowRenderer->getWin());
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
	if (input->_state)
	{
		windowRenderer->windowClosed();
		return false;
	}
	//La cosa es que los componentes le digan a su entidad lo que hacer.

	py->physicsLoop();

	//------Renderizado------
	windowRenderer->renderFrame(0);

	//------Ventana------
	windowRenderer->handleEvents();

	return true;
}

void GameManager::pushScene(Scene* newScene) {
	renderSystem->setRenderingScene(newScene->getID());
	escenas.push(newScene);
	escenas.top()->render();
}

void GameManager::popScene() {
	renderSystem->clearScene();
	escenas.pop();
	escenas.top()->render();
}

void GameManager::createMenuScene()
{
	menu->setID("menu");
	renderSystem->createScene(menu->getID());

	//--------------------------- LIGHT -----------------------------
	//Creacion de la luz en la escena
	//--------------------------- ENTIDADES ---------------------------
	EntityC* _util = new EntityC("ninja");
	pInput = _piF->Create();
	pInput->Init(_util);

	//renderSystem->squareGeneration();

	RenderComponent* Rcomp = _rF->Create();
	Rcomp->Init((_util)->_id,
		renderSystem->addOgreEntity((_util)->_id));
	(_util)->setNode(Rcomp->getOgreNode());
	(_util)->AddComponent(Rcomp);

	py->basicMesh(_util->getNode());

	menu->push(_util);
}

void GameManager::createGameScene()
{
	gamePlay->setID("gameplay");
	renderSystem->createScene(gamePlay->getID());

	EntityC* _util = new EntityC("penguin");

	RenderComponent* Rcomp = _rF->Create();
	Rcomp->Init((_util)->_id,
		RenderSystem::getSingleton()->addOgreEntity((_util)->_id));
	(_util)->setNode(Rcomp->getOgreNode());
	(_util)->AddComponent(Rcomp);

	gamePlay->push(_util);
}
