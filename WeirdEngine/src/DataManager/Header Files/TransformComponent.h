#pragma once
#include "Component.h"
#include <OgreVector.h>

class Container;

class TransformComponent : public Component {
public:
	TransformComponent() ;
	~TransformComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};
	void handleInput(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	//Getters & Setters
	Ogre::Vector3* GetPosition();
	Ogre::Vector3* GetRotation();
	Ogre::Vector3* GetScale();

	void SetPosition(Ogre::Vector3 v_);
	void SetPosition(float x_, float y_, float z_);
	void SetRotation(Ogre::Vector3 v_);
	void SetRotation(float x_, float y_, float z_);
	void SetScale(Ogre::Vector3 v_);
	void SetScale(float x_, float y_, float z_);

private:
	Ogre::Vector3 position;
	Ogre::Vector3 rotation;
	Ogre::Vector3 scale;
};