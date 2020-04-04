#include "InputListener.h"
#include "GameManager.h"
#include "Messages_defs.h"


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
		_owner->send(this, msg::Close_Win(msg::GameManager, msg::Broadcast));
		break;
	case OIS::KC_SPACE:
		_owner->send(this, msg::Prueba(msg::GameManager, msg::Broadcast));
		break;
	default:
		break;
	}

	return true;
}

bool InputListener::keyReleased(const OIS::KeyEvent& ke) {
	return false;
}
