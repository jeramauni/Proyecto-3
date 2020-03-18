#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once
#include "Scene.h"
#include "EntityC.h"

// Componentes
#include "ComponentFactory.h"

// Input
#include <InputManager.h>

class WindowRenderer;
class RenderSystem;

class GameManager {
public:
	//Constructoras
	GameManager();

	~GameManager();

	//Update
	bool update();

	//Metodos para la pila
	void pushScene(Scene *newScene);
	void popScene();

	Scene* getGamePlay() { return gamePlay; }

	// Para añadir listeners fuera de GameManager
	InputManager* getInputManager() { return mInputManager; }

protected:
	//Pila de escenas
	std::stack<Scene*> escenas;
	//Men・
	Scene* menu = new Scene("menu");
	//Juego
	Scene* gamePlay = new Scene("gameplay");
	//FIN
	Scene* theEnd = new Scene("fin");
	//Son solo escenas de prueba


	WindowRenderer* windowRenderer = nullptr;
	RenderSystem* renderSystem = nullptr;

	//Input Mng
	InputManager* mInputManager;
	//Para que el gm controle el fin de juego
	GmInputComponent* input;
	PlayerInputComponent* pInput;


	// Componentes que usa el gm
	GmInputFactory* _gmiF;

	//Esto iria en inicializacion de las entities
	PlayerInputFactory* _piF;

	RenderFactory* _rF;

	void createMenuScene();
	void createGameScene();

};
#endif