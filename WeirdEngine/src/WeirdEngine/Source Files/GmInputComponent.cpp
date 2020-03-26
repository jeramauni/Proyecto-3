#include "GmInputComponent.h"
#include "GameManager.h"



GmInputComponent::GmInputComponent() {}

GmInputComponent::~GmInputComponent() {}

void GmInputComponent::Init(GameManager* gm) {
	_gm = gm;
	listener = new GmInputListener(this);
}

void GmInputComponent::Q_Key()
{
	if (_playing) {
		_gm->popScene();
		_playing = false;
	}
	else {
		_playing = true;
		_gm->pushScene(_gm->getGamePlay());
	}
}

void GmInputComponent::Esc_Key()
{
	_state = true;
}


