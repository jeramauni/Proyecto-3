#pragma once
#include "OgreApp.h"
#include "EntityC.h"
#include <list>
#include <stack>
#include "ComponentFactory.h"

class Scene
{
private:
	std::list<EntityC*> entidades;
	std::list<EntityC*> _updates;
	//Por ahora lo hará el update
	//std::list<EntityC*> _handleEvents; 
	std::list<EntityC*> _render;
	RenderFactory* _rF;

public:
	Scene();
	void update();
	void render(OgreEasy::OgreApp * ogreApp);
	void push(EntityC* e);
};

