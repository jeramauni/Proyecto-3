#include "InputComponent.h"
#include "EntityC.h"

InputComponent::InputComponent() {}
InputComponent::~InputComponent() {}

void InputComponent::Init(EntityC* ent) {
	_entity = ent;
	//_listener = new InputListener(this);
}
/*
InputListener* InputComponent::getListener() {
	return _listener;
}
*/