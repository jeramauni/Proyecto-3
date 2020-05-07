#include "RenderComponent.h"
#include <RenderSystem.h>

#include "Container.h"
#include "ComponentFactory.h"

CREATE_REGISTER(Render);

RenderComponent::RenderComponent(Container* e) {
	_name = "Render";
	_parent = e;
}

RenderComponent::~RenderComponent() {
	_node = nullptr;
	_NameOfTheMesh.clear();
}

void RenderComponent::Init(std::unordered_map<std::string, std::string>& param) {
	_NameOfTheMesh = param.at("Mesh");
	_parent->getRSystem()->addOgreEntity(_parent->GetEntityName(), _NameOfTheMesh);
}

std::string RenderComponent::getMeshName() {
	return _NameOfTheMesh;
}

// Ogre_Node
Ogre::SceneNode* RenderComponent::getOgreNode() {
	return _node;
}

void RenderComponent::setOgreNode(Ogre::SceneNode* n) {
	_node = n;
}