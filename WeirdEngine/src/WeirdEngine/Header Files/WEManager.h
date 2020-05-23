#pragma once

#include <stack>
#include <string>
#include <json.hpp>

namespace msg {
	struct Message;
}

namespace CEGUI {
	class SubscriberSlot;
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
class AudioManager;

using json = nlohmann::json;
class Vector3;
class Vector4;


class WEManager {
	friend class EntityC;
public:
	//Constructoras
	WEManager();
	~WEManager();

	//static WEManager* _instance;
	//static WEManager* getInstance();

	// Inicializa
	void Init();

	//Update
	bool update();

	//---------Escena--------
	// Crea la escena leyendo del archivo
	void generateScene(std::string sceneName, std::string entidades);
	// Añadir widgets a la escena activa
	void createButton(std::string type, std::string widgetName, std::string text, Vector4 Perc, Vector4 Pixels);
	void addEventToButton(std::string name, CEGUI::SubscriberSlot f);
	// Cargar una layout de cegui
	void loadLayout(std::string layoutName);
	//Activar/desactivar el renderizado de cegui
	void setGUIVisible(bool b);

	//Luz
	void setLight(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

	//Metodos para la camara
	void addCameraToScene(std::string cameraName);
	void addVpToCam(std::string cameraName, Vector4 colors); //Vector4->rgba
	void moveCam(std::string camName, Vector3 pos);
	void camLookAt(std::string camName, Vector3 pos);
	void rotateCam(std::string camName, Vector4 quat);

	//Input
	void addKeyListener(InputKeyListener* iL, std::string name);
	void addMouseListener(InputMouseListener* iL, std::string name);

	//----------Mensajes------
	void send(const void* senderObj, const msg::Message& msg);
	void receive(const void* senderObj, const msg::Message& msg);

	// Cerrado del juego
	static void close();
	// Fin de la app
	static bool end;

private:
	//-----------SISTEMAS------------
	//Physics
	PhysicsEngine* py;
	//LectorDatos
	DataManager* dM;
	//Rendering
	WindowRenderer* windowRenderer;
	RenderSystem* renderSystem;
	//Audio
	AudioManager* audioManager;
	//Input Mng
	InputManager* mInputManager;
	//------------------------------------

	//Pila de escenas
	std::stack<Scene*> escenas;


	//Creacion de escena
	Container* CreateEntity(std::string& id, json prefabs, uint32_t n_entities, Vector3 position_);
	Vector3 setProperPosition(int row, int column, int layer, char xyz[3], float size_tiles, float size_layer);
	void generateEntities(Scene* scene, std::vector<std::vector<std::string>> map, json prefabs);
	void addComponentsToScene(Scene* scene, json prefabs);

	//cegui en la escena
	void setCeguiLayout(std::string layoutName);

	//Metodos para la pila
	void pushScene(Scene* newScene);
	void popScene();
};