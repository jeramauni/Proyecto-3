#pragma once
#include <OgreVector3.h>
#include <OgreNode.h>
#include "Component.h"
#include <vector>
class EntityC
{
public:
	EntityC(Ogre::SceneNode* n);
	~EntityC();

	void AddComponent(Component* c);
	void DelComponent(Component* c);

private:
	Ogre::Vector3 _position;
	std::vector<Component*> _components;
	Ogre::SceneNode* _Node;

};

