#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once
#include "Scene.h"

#include "InputManager.h"
#include "OneKeyComponent.h"

class GameManager {
public:
	GameManager() {};
	GameManager(OgreEasy::OgreApp* oa);

	~GameManager();

	bool update();

	void changeScene(Scene* newScene);

protected:
	//Pila de escenas
	std::stack<Scene*> escenas;
	//Menú
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
	OneKeyComponent* okc;
};
#endif