#pragma once

#include <stack>
#include <string>
#include <vector>

namespace msg {
	struct Message;
}

class Scene;
class Observer;
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


	//---------Escena--------
	// Devuelve la escena activa
	Scene* getTopScene();
	// Crea la escena leyendo del archivo
	void generateScene(std::string sceneName);

	//Luz
	void setLight(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

	//Metodos para la camara
	void addCameraToScene(std::string cameraName);
	void addVpToCam(std::string cameraName, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	void moveCam(std::string camName, float x, float y, float z);
	void camLookAt(std::string camName, float x, float y, float z);
	void rotateCam(std::string camName, float w, float x, float y, float z);


	//----------Mensajes------
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
};