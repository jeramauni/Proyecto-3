#pragma once
#include "Component.h"

class ButtonComponent : public Component
{
public:
	ButtonComponent();
	~ButtonComponent() {};
	//Default Init. Sets all values to 0
	void Init();

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