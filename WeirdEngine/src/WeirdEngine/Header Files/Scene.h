#pragma once
//#include <ComponentFactory.h>
#include <list>
#include <stack>
#include <string>
#include "Messages_decl.h"

class EntityC;

class Scene {
private:
	std::string _id;

	//Lista de entidades
	std::list<EntityC*> entidades;
	//Lista de listeners
	std::list<EntityC*> listeners;

public:
	Scene();
	Scene(std::string id);

	//Actualiza las entidades para que llamen a sus componentes
	void update();
	//Añade una entidad a la escena
	void addEntity(EntityC* e);

	std::string getID() { return _id; };

	virtual void send(const void* senderObj, const msg::Message& msg);
};