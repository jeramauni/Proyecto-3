#include "Container.h"

#include "Component.h"
#include "Messages_defs.h"

Container::Container() :
	EntityC() {
}

Container::Container(std::string id, WEManager* wem) :
	EntityC(id, wem) {
}

Container::~Container() {
}

//--- *UPDATE* --- *RENDER* --- *HANDLEINPUT* ---
void Container::handleInput(float time) {
	if (isActive()) {
		for (auto c : _components) {
			if (c.active && c.data->hasInput()) {
				c.data->handleInput(this, time);
			}
		}
	}
}

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
void Container::AddComponent(Component* c) {
	if (c == nullptr)
		return;

	wrapper<Component> r = { true, c };

	auto position = std::find(_components.begin(), _components.end(), r);

	if (position != _components.end()) {
		(*position).active = true;
	}
	else {
		_components.push_back(r);
	}
}

void Container::DelComponent(Component* c) {
	if (c == nullptr)
		return;

	wrapper<Component> r = { true, c };
	auto position = std::find(_components.begin(), _components.end(), r);

	if (position != _components.end()) {
		(*position).active = false;
	}
}

bool Container::hasComponent(std::string s) {
	for (auto pos : _components) {
		if (pos.data->getName(s)) {
			return true;
		}
	}

	return false;
}

Component* Container::getComponent(std::string s)
{
	for (auto pos : _components) {
		if (pos.data->getName(s)) {
			return pos.data;
		}
	}
	return nullptr;
}

void Container::reset() {
	_components.clear();
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
	//getGame()->send(senderObj, msg);
}