#include <WEManager.h>

#include "Game.h"
#include "Utilities\Vector3.h"
#include "Utilities\Vector4.h"

Game::Game() {
	_weM = new WEManager();
}

Game::~Game() {
	delete _weM;
}

void Game::Init() {
	// Iniciamos el gm
	_weM->Init();

	// Generamos la escena
	_weM->generateScene("map", "entities");

	// Boton
	//_weM->createButton("TaharezLook/Button", "TestButton", "Hello World!", { 0.5f, 0.1f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });

	//Segunda escena
	//_weM->generateScene("map2", "entities");
}

bool Game::update() {
	return _weM->update();
}