#pragma once

#include <string>

#include "Component.h"

class Container;

class ButtonComponent : public Component {
public:
	ButtonComponent(Container* ent);
	~ButtonComponent() {};
	//Default Init. Sets all values to 0
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar si es necesario
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	//Getters & Setters
	std::string GetText();
	std::string GetDestination();
	void onClick();

	void SetText(std::string _text);
	void SetDestination(std::string _destination);
private:
	std::string text;
	std::string destination;
};