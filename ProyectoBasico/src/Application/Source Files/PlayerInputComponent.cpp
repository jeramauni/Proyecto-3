#include "PlayerInputComponent.h"
#include "EntityC.h"

#include <iostream>

PlayerInputComponent::PlayerInputComponent() {}

PlayerInputComponent::~PlayerInputComponent() {}

void PlayerInputComponent::Init(EntityC* ent) {
	_entity = ent;
	_listener = new PlayerInputListener(this);
}

PlayerInputListener* PlayerInputComponent::getListener()
{
	return _listener;
}
