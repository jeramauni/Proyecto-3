#include "RenderComponent.h"

RenderComponent::RenderComponent() {
	
}

RenderComponent::~RenderComponent() {}

void RenderComponent::Init(Ogre::String name, Ogre::SceneNode* node)
{
	_NameOfTheMesh = name;
	_node = node;
}
