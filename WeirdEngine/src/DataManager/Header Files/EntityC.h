#pragma once

#include <OgreString.h>
#include <OgreSceneNode.h>
#include <vector>
#include "Component.h"
#include "Observer.h"

class EntityC : public Observer {
public:
	EntityC(Ogre::String id);
	~EntityC();

	// Añadir/quitar un componente
	void AddComponent(Component* c);
	void DelComponent(Component* c);
	Component* getComponent(Ogre::String s);

	//Recorre los componentes de la entidad y actualizan los que sean necesarios.
	void update();

	// Metodo para coger el nodo
	void setNode(Ogre::SceneNode* node);
	Ogre::SceneNode* getNode();

	//Da la posicion al nodo de Ogre
	void setPos(Ogre::Vector3 p);

	// Activar/Desactivar
	void setActive(bool sw);
	bool isActive();
	// ID de la entidad
	Ogre::String _id;

	bool receive(const void* senderObj, const msg::Message& msg);
	void send(const void* senderObj, const msg::Message& msg);

private:
	// Vector de componentes
	std::map<Ogre::String, Component*> _components;

	// Puntero al nodo de la escena
	Ogre::SceneNode* _Node = nullptr;

	bool _active;
};