#ifndef WE_MANAGER_H
#define WE_MANAGER_H

#pragma once

#include <stack>
#include <string>

namespace msg {
	class Message;
}

namespace OIS {
	class KeyListener;
	class KeyEvent;
	class MouseEvent;
}

class Scene;
class WindowRenderer;
class RenderSystem;
class InputManager;
class InputKeyListener;
class PhysicsEngine;
class DataManager;

class WEManager {
public:
	//Constructoras
	WEManager();
	~WEManager();

	// Inicializa
	void Init();

	//Update
	bool update();

	// Crea la escena leyendo del archivo
	void generateScene(std::string sceneName);

	void send(const void* senderObj, const msg::Message& msg);
	void receive(const void* senderObj, const msg::Message& msg);


private:
	//-----------SISTEMAS------------
	//Physics
	PhysicsEngine* py;
	//LectorDatos
	DataManager* dM;
	//Rendering
	WindowRenderer* windowRenderer;
	RenderSystem* renderSystem;
	//Input Mng
	InputManager* mInputManager;
	InputKeyListener* input;
	//------------------------------------

	//Pila de escenas
	std::stack<Scene*> escenas;

	// Fin de bucle de juego
	bool end;
	void close();

	//Metodos para la pila
	void pushScene(Scene* newScene);
	void popScene();

	// Input
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

	//virtual bool mousePressed(const OIS::MouseEvent& ke) {};
	//virtual bool mouseReleased(const OIS::MouseEvent& ke) {};
};
#endif