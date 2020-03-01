#pragma once
#include "Component.h"

#include <OgreString.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>

class RenderComponent: public Component {
public:
	//RenderComponent(Ogre::SceneManager* scene, Ogre::String s, Ogre::SceneNode* n);
	RenderComponent(Ogre::String name, Ogre::SceneNode* node);
	~RenderComponent();

	//Ogre::Entity* getOgreEntity() { return _entPointer; }
	Ogre::SceneNode* getOgreNode() { return _node; }

private:
	Ogre::SceneNode* _node;
	Ogre::String _NameOfTheMesh;
	//Ogre::Entity* _entPointer;
};