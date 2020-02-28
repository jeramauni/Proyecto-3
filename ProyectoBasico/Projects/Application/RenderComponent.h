#pragma once
#include "Component.h"
#include <OgreString.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
class RenderComponent: public Component
{
public:
	RenderComponent(Ogre::SceneManager* scene, Ogre::String s, Ogre::SceneNode* n);
	~RenderComponent();
	Ogre::Entity* getOgreEntity();

private:
	Ogre::String _NameOfTheMesh;
	Ogre::Entity* _entPointer;
};

