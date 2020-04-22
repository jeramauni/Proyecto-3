#pragma once
#include "Component.h"

#include <OgreEntity.h>
#include <OgreSceneManager.h>

class RenderComponent : public Component {
public:
	RenderComponent();
	~RenderComponent();

	void Init(std::unordered_map<std::string, std::string>& param);

	//Getters and setters
	Ogre::SceneNode* getOgreNode();
	std::string getMeshName();

	void setOgreNode(Ogre::SceneNode* n);

private:

	Ogre::SceneNode* _node;
	std::string _NameOfTheMesh;
};