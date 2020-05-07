#pragma once

#include <stack>
#include <string>
#include <json.hpp>

namespace msg {
	struct Message;
}

class Scene;
class Container;
class EntityC;

class WindowRenderer;
class RenderSystem;
class InputManager;
class InputKeyListener;
class InputMouseListener;
class PhysicsEngine;
class DataManager;

using json = nlohmann::json;
class Vector3;

class WEManager {
	friend class EntityC;
public:
	//Constructoras
	WEManager();
	~WEManager();

	// Inicializa
	void Init();

	//Update
	bool update();

	//---------Escena--------
	// Crea la escena leyendo del archivo
	void generateScene(std::string sceneName, std::string entidades);

	//Luz
	void setLight(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

	//Metodos para la camara
	void addCameraToScene(std::string cameraName);
	void addVpToCam(std::string cameraName, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	void moveCam(std::string camName, float x, float y, float z);
	void camLookAt(std::string camName, float x, float y, float z);
	void rotateCam(std::string camName, float w, float x, float y, float z);

	//Input
	void addKeyListener(InputKeyListener* iL, std::string name);
	void addMouseListener(InputMouseListener* iL, std::string name);

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
	//------------------------------------

	//Pila de escenas
	std::stack<Scene*> escenas;

	// Fin de bucle de juego
	bool end;
	void close();

	//Creacion de escena
	Container* CreateEntity(std::string& id, json prefabs, uint32_t n_entities, Vector3 position_);
	Vector3 setProperPosition(int row, int column, int layer, char xyz[3], float size_tiles, float size_layer);
	void generateEntities(Scene* scene, std::vector<std::vector<std::string>> map, json prefabs);
	void addComponentsToScene(Scene* scene, json prefabs);

	//Metodos para la pila
	void pushScene(Scene* newScene);
	void popScene();
};