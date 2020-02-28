#include "RenderComponent.h"

RenderComponent::RenderComponent(Ogre::SceneManager* scene, Ogre::String s, Ogre::SceneNode* n)
{
	_NameOfTheMesh = s;
	_entPointer = scene->createEntity(_NameOfTheMesh);
	n->attachObject(_entPointer);
}

RenderComponent::~RenderComponent()
{
}


Ogre::Entity* RenderComponent::getOgreEntity() {
	return _entPointer;
}