#include <WEManager.h>

#include "Game.h"

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
	_weM->generateScene("map.txt");
}

bool Game::update() {
	return _weM->update();
}