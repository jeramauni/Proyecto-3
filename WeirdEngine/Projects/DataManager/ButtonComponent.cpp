#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() {
	name = "button";
}

void ButtonComponent::Init()
{
	text = "Sample text";
}

//GETTERS

std::string ButtonComponent::GetText() { return text; }
std::string ButtonComponent::GetDestination(){ return destination; }

void ButtonComponent::onClick()
{
}

//SETTERS
void ButtonComponent::SetText(std::string _text){ text = _text; }
void ButtonComponent::SetDestination(std::string _destination) { destination = _destination; }
