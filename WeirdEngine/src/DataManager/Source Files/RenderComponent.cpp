#include "RenderComponent.h"
#include "ComponentFactory.h"
DEFINE_FACTORY(Render);
RenderComponent::RenderComponent() {
	
}

RenderComponent::~RenderComponent() {}

void RenderComponent::Init(std::string name, Ogre::SceneNode* node)
{
	_NameOfTheMesh = name;
	_node = node;
}