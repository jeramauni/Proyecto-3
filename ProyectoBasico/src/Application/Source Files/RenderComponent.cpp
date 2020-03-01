#include "RenderComponent.h"

RenderComponent::RenderComponent(Ogre::String name, Ogre::SceneNode* node) {
	_NameOfTheMesh = name;
	_node = node;
}

RenderComponent::~RenderComponent() {}
