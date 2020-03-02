#pragma once
#include "Scene.h"

class GameManager
{
protected:
	//Pila de escenas
	std::stack<Scene*> escenas;
	int i = 10000;
	//Menú
	Scene* menu = new Scene();
	//Juego
	Scene* gamePlay = new Scene();
	//FIN
	Scene* theEnd = new Scene();

	//Son solo escenas de prueba

	OgreEasy::OgreApp* ogreApp;

public:
	GameManager() {};
	GameManager(OgreEasy::OgreApp* oa);
	
	~GameManager();
	
	bool update();

	void changeScene(Scene* newScene);
};