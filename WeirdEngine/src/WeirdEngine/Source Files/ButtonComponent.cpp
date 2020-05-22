#include "ButtonComponent.h"
#include "ComponentFactory.h"

CREATE_REGISTER(Button);

ButtonComponent::ButtonComponent(Container* ent) {
	_name = "button";
}

void ButtonComponent::Init(std::unordered_map<std::string, std::string>& param) {
	text = "Sample text";
}

//GETTERS

std::string ButtonComponent::GetText() { return text; }
std::string ButtonComponent::GetDestination() { return destination; }

void ButtonComponent::onClick() {

}

//SETTERS
void ButtonComponent::SetText(std::string _text) { text = _text; }
void ButtonComponent::SetDestination(std::string _destination) { destination = _destination; }