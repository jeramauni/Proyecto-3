#pragma once
//#include <ComponentFactory.h>
#include <list>
#include <stack>
#include <string>

class EntityC;

class Scene {
private:
	std::string _id;

	//Lista de entidades
	std::list<EntityC*> entidades;

	//GmInputFactory* _rF;

public:
	Scene();
	Scene(std::string id);

	//Actualiza las entidades para que llamen a sus componentes
	void update();
	//Añade una entidad a la escena
	void addEntity(EntityC* e);

	std::string getID() { return _id; };
};

