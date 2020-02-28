#include "EntityC.h"




EntityC::EntityC(Ogre::SceneNode* n) {
	_position.x = 0; _position.y = 0; _position.z = 0;
	_Node = n;
}

EntityC::~EntityC()
{
}

void EntityC::AddComponent(Component* c)
{
	_components.push_back(c);
}

void EntityC::DelComponent(Component* c)
{
	std::vector<Component*>::iterator pos =
		std::find(_components.begin(), _components.end(), c);
	if (pos != _components.end()) {
		_components.erase(pos); 
	}
}

void EntityC::setOgreNode(Ogre::SceneNode* n)
{
	_Node = n;
}
