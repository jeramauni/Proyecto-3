#include "RenderComponent.h"
#include "ComponentFactory.h"
DEFINE_FACTORY(Render);

void RenderComponent::Init(std::string name, Ogre::SceneNode* node)
{
	_NameOfTheMesh = name;
	_node = node;
}

void RenderComponent::Init(std::unordered_map<std::string, std::string>& param)
{
	_NameOfTheMesh = param.at("Mesh");
}
