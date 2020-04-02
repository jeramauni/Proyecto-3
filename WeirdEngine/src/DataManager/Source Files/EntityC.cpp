#include "EntityC.h"
#include "TransformComponent.h"
#include "Messages_defs.h"
#include <iostream>

EntityC::EntityC(Ogre::String id) : _id(id) {
	_active = true;
}

EntityC::~EntityC() {}

void EntityC::update() {
	if (_active) {
		std::cout << "Actualizando entidad: " + this->_id + "\n";
	}
}

void EntityC::AddComponent(Component* c) {
	_components.insert({ c->name, c });
}

void EntityC::DelComponent(Component* c) {
	_components.erase(c->name);
}


Component* EntityC::getComponent(Ogre::String s)
{
	return _components.at(s);
}

void EntityC::setNode(Ogre::SceneNode* node) {
	_Node = node;
	_Node->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));
}

Ogre::SceneNode* EntityC::getNode()
{
	return _Node;
}

void EntityC::setPos(Ogre::Vector3 p) {
	_Node->setPosition(p);
	static_cast<TransformComponent*>(this->getComponent("transform"))->SetPosition(p);
}

void EntityC::setActive(bool sw)
{
	_active = sw;
}

bool EntityC::isActive()
{
	return _active;
}

void EntityC::receive(const void* senderObj, const msg::Message& msg)
{
	if (msg.type_ == msg::PRUEBA)
		std::cout << "vaya";
}
