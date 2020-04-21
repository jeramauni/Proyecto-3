#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once
#include "Scene.h"
#include "Messages_decl.h"

// InputManager
#include <InputManager.h>

class WindowRenderer;
class RenderSystem;
class InputManager;
class PhysicsEngine;
class DataManager;

class GameManager {
public:
	//Constructoras
	GameManager();
	~GameManager();

	// Inicializa
	void Init();

	//Update
	bool update();

	// Crea la escena leyendo del archivo
	void generateScene(std::string sceneName);

	// Para coger el inputMng
	InputManager* getInputMg() { return mInputManager; };

	void send(const void* senderObj, const msg::Message& msg);
	void receive(const void* senderObj, const msg::Message& msg);

private:
	//-----------SISTEMAS------------
	//Physics
	PhysicsEngine* py;
	//LectorDatos
	DataManager* dM;
	//Rendering
	WindowRenderer* windowRenderer = nullptr;
	RenderSystem* renderSystem = nullptr;
	//Input Mng
	InputManager* mInputManager;
	//------------------------------------

	//Pila de escenas
	std::stack<Scene*> escenas;

	// Fin de bucle de juego
	bool end = false;
	void close();

	//Metodos para la pila
	void pushScene(Scene* newScene);
	void popScene();
};
#endif