#pragma once
#include "Component.h"
#include <OgreVector.h>

class TransformComponent : public Component
{
public:
	TransformComponent() {};
	~TransformComponent() {};
	//Default Init. Sets all values to 0
	void Init();
	//Inits with specified Ogre::Vector3 vectors
	void Init(const Ogre::Vector3& position_,const Ogre::Vector3& rotation_,const Ogre::Vector3& scale_);
	//Inits with specified Ogre::Vector3 components values
	void Init(float positionx_, float positiony_, float positionz_, float rotationx_, float rotationy_, float rotationz_, float scalex_, float scaley_, float scalez_);

	//Getters and Setters
	Ogre::Vector3 GetPosition();
	Ogre::Vector3 GetRotation();
	Ogre::Vector3 GetScale();

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

