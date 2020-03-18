#include "PlayerInputListener.h"

#include <iostream>

PlayerInputListener::PlayerInputListener(PlayerInputComponent* ow)
{
	_owner = ow;
}

bool PlayerInputListener::keyPressed(const OIS::KeyEvent& ke)
{
	switch (ke.key) {
	case OIS::KC_W:
		std::cout << "Moverse W!\n";
		break;
	case OIS::KC_A:
		std::cout << "Moverse A!\n";
		break;
	case OIS::KC_S:
		std::cout << "Moverse S!\n";
		break;
	case OIS::KC_D:
		std::cout << "Moverse D!\n";
		break;
	default:
		break;
	}

	return true;
}

bool PlayerInputListener::keyReleased(const OIS::KeyEvent& ke)
{
	return false;
}
