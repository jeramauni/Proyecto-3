#pragma once
#include "Component.h"

#include <OgreEntity.h>
#include <OgreSceneManager.h>

class RenderComponent: public Component {
public:
	RenderComponent();
	~RenderComponent();
	void Init(std::string name, Ogre::SceneNode* node);
	void Init() {};

	Ogre::SceneNode* getOgreNode() { return _node; }

private:
	Ogre::SceneNode* _node;
	std::string _NameOfTheMesh;
};