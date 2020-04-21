#include <GameManager.h>

#include "Game.h"
#include "InputListener.h"

Game::Game() {
	_gm = new GameManager();
	input = new InputListener(_gm);
}

Game::~Game() {
	delete _gm;
	delete input;
}

void Game::Init() {
	// Iniciamos el gm
	_gm->Init();
	// Añadimos al controlador de input las teclas que se usaran en este juego
	_gm->getInputMg()->addKeyListener(input, "RetroRunnerKeys");
	// Generamos la escena
	_gm->generateScene("map.txt");

}

bool Game::update() {
	return _gm->update();
}
