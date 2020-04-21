#include "TransformComponent.h"

void TransformComponent::Init(const Ogre::Vector3& position_, const Ogre::Vector3& rotation_, const Ogre::Vector3& scale_)
{
	position = position_;
	rotation = rotation_;
	scale = scale_;
}

void TransformComponent::Init(float positionx_, float positiony_, float positionz_, float rotationx_, float rotationy_, float rotationz_, float scalex_, float scaley_, float scalez_)
{
	position = Ogre::Vector3(positionx_, positiony_, positionz_);
	rotation = Ogre::Vector3(rotationx_, rotationy_, rotationz_);
	scale = Ogre::Vector3(scalex_, scaley_, scalez_);
}

//GETTERS
Ogre::Vector3 TransformComponent::GetPosition() { return position; }
Ogre::Vector3 TransformComponent::GetRotation() { return rotation; }
Ogre::Vector3 TransformComponent::GetScale() { return scale; }

//SETTERS
void TransformComponent::SetPosition(Ogre::Vector3 v_) { position = v_; }
void TransformComponent::SetPosition(float x_, float y_, float z_) { position = Ogre::Vector3(x_, y_, z_); }

void TransformComponent::SetRotation(Ogre::Vector3 v_) { rotation = v_; }
void TransformComponent::SetRotation(float x_, float y_, float z_) { rotation = Ogre::Vector3(x_, y_, z_); }

void TransformComponent::SetScale(Ogre::Vector3 v_) { scale = v_; }
void TransformComponent::SetScale(float x_, float y_, float z_) { scale = Ogre::Vector3(x_, y_, z_); }
