#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once
#include "Scene.h"
#include "EntityC.h"
#include "Messages_decl.h"

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
	void addListener(InputListener *iL, std::string name);

	//Metodos para la pila
	void pushScene(Scene* newScene);
	void popScene();

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
	//Temp del input
	InputListener* iList;
	//------------------------------------

	//Pila de escenas
	std::stack<Scene*> escenas;
};
#endif