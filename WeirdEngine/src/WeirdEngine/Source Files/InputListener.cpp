#include "InputListener.h"
#include "GameManager.h"

#include <iostream>

InputListener::InputListener(GameManager* ow) {
	_owner = ow;
}

bool InputListener::keyPressed(const OIS::KeyEvent& ke) {
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
	case OIS::KC_ESCAPE:
		_owner->close();
	default:
		break;
	}

	return true;
}

bool InputListener::keyReleased(const OIS::KeyEvent& ke) {
	return false;
}
