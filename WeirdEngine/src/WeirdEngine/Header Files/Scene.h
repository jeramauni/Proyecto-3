#pragma once
#include "OgreApp.h"
#include <ComponentFactory.h>
#include <list>
#include <stack>
#include <string>
#include <EntityC.h>

class Scene
{
private:
	std::string _id;
	std::list<EntityC*> entidades;
	std::list<EntityC*> _updates;
	//Por ahora lo hará el update
	//std::list<EntityC*> _handleEvents; 
	std::list<EntityC*> _render;
	RenderFactory* _rF;

public:
	Scene();
	Scene(std::string id);

	void update();
	void render();
	void push(EntityC* e);

	std::string getID() { return _id; };
	void setID(std::string id);
};

