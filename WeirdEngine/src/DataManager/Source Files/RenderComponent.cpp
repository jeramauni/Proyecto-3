#include "RenderComponent.h"
#include "ComponentFactory.h"
DEFINE_FACTORY(Render);

RenderComponent::RenderComponent() 
{
	name = "Render";
}

RenderComponent::~RenderComponent() 
{
	_node = nullptr;
	_NameOfTheMesh.clear();
}

void RenderComponent::Init(std::unordered_map<std::string, std::string>& param)
{
	_NameOfTheMesh = param.at("Mesh");
}

Ogre::SceneNode* RenderComponent::getOgreNode() 
{
	return _node;
}

std::string RenderComponent::getMeshName()
{
	return _NameOfTheMesh;
}

void RenderComponent::setOgreNode(Ogre::SceneNode* n)
{
	_node = n;
}
