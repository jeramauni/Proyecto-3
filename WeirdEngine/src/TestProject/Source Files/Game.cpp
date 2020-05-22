#include <WEManager.h>

#include <iostream>
#include <CEGUI/CEGUI.h> //FEISIMO

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

	_weM->generateScene("menu", "entities");
	_weM->loadLayout("EmptyWindow");

	// Generamos la escena
	//_weM->generateScene("map", "entities");

	// Boton
	_weM->createButton("TaharezLook/Button", "TestButton", "EXIT", { 0.5f, 0.1f, 0.1f, 0.2f }, { 0.0, 0.0 ,0.0 ,0.0 });
	//CEGUI::SubscriberSlot ev = &Game::EventEnd;
	_weM->addEventToButton("TestButton", &Game::EventEnd);

	//Segunda escena
	//_weM->generateScene("map2", "entities");
}

void Game::EventEnd() {
	std::cout << "ENDINNNNG\n";
	WEManager::close();
}


bool Game::update() {
	return _weM->update();
}
