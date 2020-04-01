#include "GameManager.h"
#include <WindowRenderer.h>
#include <RenderSystem.h>

// PhysicsManager
#include <PhysicsEngine.h>
// InputManager
#include <InputManager.h>
#include "InputListener.h"
// DataManager
#include<DataManager.h>

GameManager::GameManager() {
}

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

	////-----*INPUT DE CADA JUEGO*-------------
	// Este input se crearia en cada juego con las teclas especificas que se van a usar en el juego, y se usaria para que
	// cuando el input detecta entrada de una de las teclas, el gm mande un mensaje broadcast a todas las entidades 
	// de la escena, afectadas por ese emnsaje, tambien se lo mandara el mensaje a si mismo (al gm) para actuar en funcion
	// al mensaje si tiene que hacerlo
	iList = new InputListener(this);
	mInputManager->addKeyListener(iList, "JuegosKeys");

	//-------------------------- MATERIALS -------------------------------
	//Carga de los materiales que usaremos
	renderSystem->materialGeneration(" Mat");


	/// Esto va en otro ladu
	generateScene("nivel1.json");
}

// Genera la escena leyendo del archivo de datos
void GameManager::generateScene(std::string sceneName) {
	//Creamos la escena
	Scene *mScene = new Scene(sceneName);
	renderSystem->createScene(mScene->getID());

	//Leemos las entidades del archivo de datos
	std::vector<EntityC*> ent = dM->LoadSceneEntities(sceneName);

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
	if (end) {
		windowRenderer->windowClosed();
		return false;
	}
	//La cosa es que los componentes le digan a su entidad lo que hacer.

	// Fisicas
	py->physicsLoop();

	//Update
	//escenas.top()->update();

	//------Renderizado------
	windowRenderer->renderFrame(0);

	//------Ventana------
	windowRenderer->handleEvents();

	return true;
}

void GameManager::pushScene(Scene* newScene) {
	renderSystem->setRenderingScene(newScene->getID());
	escenas.push(newScene);
}

void GameManager::popScene() {
	escenas.pop();
	renderSystem->setRenderingScene(escenas.top()->getID());
}

void GameManager::createMenuScene()
{
	//menu->setID("menu");
	menu = new Scene("menu");
	renderSystem->createScene(menu->getID());

	//--------------------------- ENTIDADES ---------------------------
	//ninja
	/*
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
	*/

	//plano
	/*
	EntityC* _plano = new EntityC("plano");
	Rcomp->Init((_plano)->_id,
		renderSystem->addOgreEntity((_plano)->_id));
	(_plano)->setNode(Rcomp->getOgreNode());
	(_plano)->AddComponent(Rcomp);

	_plano->getNode()->setPosition(_plano->getNode()->getPosition().x, _plano->getNode()->getPosition().y - 200, _plano->getNode()->getPosition().z);
	_plano->getNode()->pitch(Ogre::Radian(10));

	py->planeMesh(_plano->getNode());

	menu->addEntity(_util);
	menu->addEntity(_plano);
	*/
}

void GameManager::createGameScene() {
	//gamePlay->setID("gameplay");
	/*
	gamePlay = new Scene("gameplay");
	renderSystem->createScene(gamePlay->getID());

	EntityC* _util = new EntityC("penguin");

	RenderComponent* Rcomp = _rF->Create();
	Rcomp->Init((_util)->_id,
		RenderSystem::getSingleton()->addOgreEntity((_util)->_id));
	(_util)->setNode(Rcomp->getOgreNode());
	(_util)->AddComponent(Rcomp);

	gamePlay->addEntity(_util);
	*/
}