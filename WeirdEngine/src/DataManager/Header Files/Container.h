#pragma once

#include "EntityC.h"
#include <vector>

class Component;

/*
 *
 */
class Container : public EntityC {
public:
	Container();
	Container(std::string id, WEManager* wem);
	virtual ~Container();

	virtual void handleInput(float time);
	virtual void update(float time);

	// Añadir/quitar/comprobar un componente
	void AddComponent(Component* c);
	void DelComponent(Component* c);
	bool hasComponent(std::string s);
	Component* getComponent(std::string s);

	void reset(); // removes all components

	virtual void receive(const void* senderObj, const msg::Message& msg);

	// used by components to send message at the level of container
	void localSend(const void* senderObj, const msg::Message& msg);

	// this will be used by components to send message globally
	void globalSend(const void* senderObj, const msg::Message& msg);
private:
	void broadcastToLocalComponents(const void* senderObj, const msg::Message& msg);

	template<typename T>
	struct wrapper {
		bool active;
		Component* data;

		bool operator==(const wrapper<Component>& other) const {
			return other.data == data;
		}
	};

	std::vector<wrapper<Component>> _components;
};