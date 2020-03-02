#pragma once
#include "OgreApp.h"
#include "EntityC.h"
#include <list>
#include <stack>


class Scene
{
private:
	std::list<EntityC*> entidades;

public:
	Scene() {};
	void update();
	void render(OgreEasy::OgreApp * ogreApp);
	void push(EntityC* e);
};

