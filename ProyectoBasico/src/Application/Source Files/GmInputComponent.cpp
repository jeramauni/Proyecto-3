#include "GmInputComponent.h"
#include "GameManager.h"

GmInputComponent::GmInputComponent(GameManager* gm) {
	_gm = gm;
}

GmInputComponent::~GmInputComponent() {}

bool GmInputComponent::keyPressed(const OIS::KeyEvent& ke) {
	switch (ke.key) {
	case OIS::KC_ESCAPE:
		_state = true;
		break;
	case OIS::KC_Q:
		if (_playing) {
			_gm->popScene();
			_playing = false;
		}
		else {
			_playing = true;
			_gm->pushScene(_gm->getGamePlay());
		}
		break;
	}

	return false;
}

bool GmInputComponent::keyReleased(const OIS::KeyEvent& ke) {
	return false;
}
