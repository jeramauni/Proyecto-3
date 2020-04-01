#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once
#include "Scene.h"
#include "EntityC.h"

class WindowRenderer;
class RenderSystem;
class InputManager;
class PhysicsEngine;
class DataManager;

class InputListener;

class GameManager {
public:
	//Constructoras
	GameManager();
	~GameManager();

	// Inicializa
	void Init();

	bool end = false;
	void close() { end = true; };

	// Crea la escena leyendo del archivo
	void generateScene(std::string sceneName);

	//Update
	bool update();

	// Para añadir listeners fuera de GameManager
	InputManager* getInputManager() { return mInputManager; }

	//Temp
	Scene* getGamePlay() { return gamePlay; }

	//Metodos para la pila
	void pushScene(Scene* newScene);
	void popScene();
protected:

	//-------------------------
	//MainMenu
	Scene* menu;
	//Juego
	Scene* gamePlay;
	//FIN
	Scene* theEnd;
	//Son solo escenas de prueba
	//-----

	void createMenuScene();
	void createGameScene();
private:
	//Physics
	PhysicsEngine* py;

	//LectorDatos
	DataManager* dM;

	//Rendering
	WindowRenderer* windowRenderer = nullptr;
	RenderSystem* renderSystem = nullptr;

	//Input Mng
	InputManager* mInputManager;
	//Temp del input
	InputListener* iList;

	//Pila de escenas
	std::stack<Scene*> escenas;
};
#endif