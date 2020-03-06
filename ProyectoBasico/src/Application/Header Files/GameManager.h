#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once
#include "Scene.h"

#include "InputManager.h"
#include "GmInputComponent.h"

class GameManager {
public:
	//Constructoras
	GameManager() {};
	GameManager(OgreEasy::OgreApp* oa);

	~GameManager();

	//Update
	bool update();

	//Metodos para la pila
	void pushScene(Scene *newScene);
	void popScene();
	void changeScene(Scene* newScene);

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


	// OgreApp
	OgreEasy::OgreApp* ogreApp;

	//Input Mng
	InputManager* mInputManager;
	//Temp
	GmInputComponent* input;
};
#endif