#pragma once
#include "Component.h"

#include <OgreEntity.h>
#include <OgreSceneManager.h>

class Container;

class RenderComponent : public Component {
public:
	RenderComponent();
	~RenderComponent();

	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};
	void handleInput(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	//Getters and setters
	Ogre::SceneNode* getOgreNode();
	std::string getMeshName();

	void setOgreNode(Ogre::SceneNode* n);

private:
	Ogre::SceneNode* _node;
	std::string _NameOfTheMesh;
};