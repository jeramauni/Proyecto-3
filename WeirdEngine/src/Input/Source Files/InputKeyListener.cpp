#include "InputKeyListener.h"

//#include <WEManager.h>
//#include <Messages_defs.h>
//#include <Messages_decl.h>

#include <iostream>

InputKeyListener::InputKeyListener(WEManager* ow) {
	_owner = ow;
}

bool InputKeyListener::keyPressed(const OIS::KeyEvent& ke) {
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
		//_owner->send(this, msg::Close_Win(msg::WEManager, msg::Broadcast));
		break;
	case OIS::KC_SPACE:
		//_owner->send(this, msg::Prueba(msg::WEManager, msg::Broadcast));
		break;
	default:
		break;
	}

	return true;
}

bool InputKeyListener::keyReleased(const OIS::KeyEvent& ke) {
	return false;
}
