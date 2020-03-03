#include "..\Header Files\OneKeyComponent.h"

bool OneKeyComponent::keyPressed(const OIS::KeyEvent& ke) {
	switch (ke.key) {
	case OIS::KC_ESCAPE:
		//shutDown = true;
		state = true;
		break;
	}
	return false;
}

bool OneKeyComponent::keyReleased(const OIS::KeyEvent& ke) {
	return false;
}
