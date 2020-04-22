#pragma once

#include <OgreSceneNode.h>
#include <vector>
#include "Component.h"
#include "Observer.h"

class EntityC : public Observer {
public:
	EntityC(std::string id);
	~EntityC();

	// Añadir/quitar un componente
	void AddComponent(Component* c);
	void DelComponent(Component* c);
	Component* getComponent(std::string s);

	//Recorre los componentes de la entidad y actualizan los que sean necesarios.
	void update();

	// Setter/getter Node
	void setNode(Ogre::SceneNode* node);
	Ogre::SceneNode* getNode();

	//Da la posicion al nodo de Ogre
	void setPos(Ogre::Vector3 p);

	// Activar/Desactivar
	void setActive(bool sw);
	bool isActive();

	// ID de la entidad
	std::string _id;

	bool receive(const void* senderObj, const msg::Message& msg);
	void send(const void* senderObj, const msg::Message& msg);

private:
	// Vector de componentes
	std::map<std::string, Component*> _components;

	// Puntero al nodo de la escena
	Ogre::SceneNode* _Node = nullptr;

	bool _active;
};