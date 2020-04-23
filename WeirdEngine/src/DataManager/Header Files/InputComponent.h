#pragma once

#include <string>
#include <unordered_map>

#include "Component.h"
#include "Messages_decl.h"

class Container;

class InputComponent : public Component {
public:
	InputComponent(Container* c) {};
	~InputComponent() {};

	virtual void Init(std::unordered_map<std::string, std::string>& param) = 0;

	// By default components do not do anything when receiving a message.
	// Only those interested will implement this method
	virtual void receive(Container* c, const msg::Message& msg) = 0;

	// Update
	virtual void update(Container* c, float time) = 0;

protected:
	Container* _owner;
};