#pragma once
#include "Component.h"

#include <OgreEntity.h>
#include <OgreSceneManager.h>

class RenderComponent : public Component {
public:
	//RenderComponent(Ogre::SceneManager* scene, std::string s, Ogre::SceneNode* n);
	RenderComponent() { name = "Render"; };
	~RenderComponent() {};
	void Init(std::string name, Ogre::SceneNode* node);
	void Init(std::unordered_map<std::string, std::string>& param);

	//Ogre::Entity* getOgreEntity() { return _entPointer; }
	Ogre::SceneNode* getOgreNode() { return _node; }
	void setOgreNode(Ogre::SceneNode* n) { _node = n; }
	std::string getMeshName() { return _NameOfTheMesh; }
private:
	Ogre::SceneNode* _node;
	std::string _NameOfTheMesh;
	//Ogre::Entity* _entPointer;
};