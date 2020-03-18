#pragma once

#include "EntityC.h"
#include "ComponentFactory.h"
#include <list>
#include <stack>
#include <string>

class Scene
{
private:
	std::list<EntityC*> entidades;
	std::list<EntityC*> _updates;
	//Por ahora lo hará el update
	//std::list<EntityC*> _handleEvents; 
	std::list<EntityC*> _render;
	std::string _id;
	RenderFactory* _rF;

	// temp

public:
	Scene();
	Scene(std::string id);
	void update();
	void render();
	void push(EntityC* e);
	std::string getID() { return _id; };
};

