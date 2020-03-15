#pragma once

#include "EntityC.h"
#include "ComponentFactory.h"
#include <list>
#include <stack>

class Scene
{
private:
	std::list<EntityC*> entidades;
	std::list<EntityC*> _updates;
	//Por ahora lo hará el update
	//std::list<EntityC*> _handleEvents; 
	std::list<EntityC*> _render;
	RenderFactory* _rF;

	// temp

public:
	Scene();
	void update();
	void render();
	void push(EntityC* e);
};

