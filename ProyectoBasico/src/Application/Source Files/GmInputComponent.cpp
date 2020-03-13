#include "GmInputComponent.h"
#include "GameManager.h"



GmInputComponent::GmInputComponent() {}

GmInputComponent::~GmInputComponent() {}

void GmInputComponent::Init(GameManager* gm) {
	_gm = gm;
}

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
	default:
		break;
	}

	return false;
}

bool GmInputComponent::keyReleased(const OIS::KeyEvent& ke) {
	return false;
}
