#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once
#include "Scene.h"
#include "EntityC.h"
#include "RenderUtilities.h"

// Componentes
#include "ComponentFactory.h"

// Physics
//#include <PhysicsEngine.h> //Error

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
	Scene* menu = new Scene();
	//Juego
	Scene* gamePlay = new Scene();
	//FIN
	Scene* theEnd = new Scene();
	//Son solo escenas de prueba


	WindowRenderer* windowRenderer = nullptr;
	RenderSystem* renderSystem = nullptr;

	//Physics
	//PhysicsEngine* py;

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