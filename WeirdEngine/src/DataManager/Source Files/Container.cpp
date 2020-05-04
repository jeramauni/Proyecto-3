#include "Container.h"

#include "Component.h"
#include "InputComponent.h"
#include "Messages_defs.h"

/*
Container::Container() :
	EntityC() {
}
*/

Container::Container(std::string id, WEManager* wem) :
	EntityC(id, wem) {
}

Container::~Container() {
}

//--- *UPDATE* ---
void Container::update(float time) {
	if (isActive()) {
		for (auto c : _components) {
			if (c.active && c.data->hasUpdate()) {
				c.data->update(this, time);
			}
		}
	}
}

//---------------------

//---Componentes---
//Añadir un componente
void Container::AddComponent(Component* c) {
	AddC(_components, c);
}

void Container::AddComponent(InputComponent* c) {
	AddC(_InputComponents, c);
}

//Eliminar un componente
void Container::DelComponent(Component* c) {
	removeC(_components, c);
}

void Container::DelComponent(InputComponent* c) {
	removeC(_InputComponents, c);
}

// Comprobar si tiene un componente
bool Container::hasComponent(std::string s) {
	for (auto pos : _components) {
		if (pos.data->getName(s)) {
			return true;
		}
	}
	for (auto pos : _InputComponents) {
		if (pos.data->getName(s)) {
			return true;
		}
	}

	return false;
}

// Obtener un componente
Component* Container::getComponent(std::string s) {
	for (auto pos : _components) {
		if (pos.data->getName(s)) {
			return pos.data;
		}
	}
	return nullptr;
}

InputComponent* Container::getInputComponent(std::string s) {
	for (auto pos : _InputComponents) {
		if (pos.data->getName(s)) {
			return pos.data;
		}
	}
	return nullptr;
}

//Reset
void Container::reset() {
	_components.clear();
	_InputComponents.clear();
}
//-------------------------


//----Mensajes----
void Container::receive(const void* senderObj, const msg::Message& msg) {
	broadcastToLocalComponents(senderObj, msg);
}

void Container::broadcastToLocalComponents(
	const void* senderObj, const msg::Message& msg) {
	for (auto c : _components) {
		if (c.data != senderObj && c.active) {
			c.data->receive(this, msg);
		}
	}
}

void Container::localSend(const void* senderObj, const msg::Message& msg) {
	broadcastToLocalComponents(senderObj, msg);
}

void Container::globalSend(const void* senderObj, const msg::Message& msg) {
	getGame()->send(senderObj, msg);
}