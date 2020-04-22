#pragma once
#include "Component.h"
#include <OgreVector.h>

class TransformComponent : public Component
{
public:
	TransformComponent() { name = "Transform"; };
	~TransformComponent() {};
	//Default Init. Sets all values to 0
	void Init(std::unordered_map<std::string, std::string>& param);

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