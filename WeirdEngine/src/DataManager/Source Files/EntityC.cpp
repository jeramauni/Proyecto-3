#include "EntityC.h"
#include "Messages_defs.h"

#include <WEManager.h>
#include <iostream>

class SceneNode;

EntityC::EntityC(std::string name, WEManager* wem) {
	_entName = name;
	_weM = wem;
	_active = true;
}

EntityC::~EntityC() {}

// Manager
WEManager* EntityC::getGame() const {
	return _weM;
}

void EntityC::setGame(WEManager* wem) {
	_weM = wem;
}

// Nodo
void EntityC::setNode(Ogre::SceneNode* node) {
	_Node = node;
}

Ogre::SceneNode* EntityC::getNode() {
	return _Node;
}

// Posicion
void EntityC::setPos(const Ogre::Vector3& p) {
	_Node->setPosition(p);
}

Ogre::Vector3 EntityC::getPosition() const {
	return _Node->getPosition();
}

void EntityC::setActive(bool a) {
	_active = a;
}

bool EntityC::isActive() {
	return _active;
}

std::string EntityC::GetEntityName()
{
	return _entName;
}

void EntityC::receive(const void* senderObj, const msg::Message& msg) {
	// By default objects do no do anything when receiving a message.
	// Only those interested will implement this method
}

void EntityC::init() {}