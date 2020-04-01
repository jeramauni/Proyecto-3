#include "GmInputListener.h"
#include <iostream>
#include "GmInputComponent.h"

GmInputListener::GmInputListener(GmInputComponent* ow)
{
	owner = ow;
}

bool GmInputListener::keyPressed(const OIS::KeyEvent& ke)
{
	switch (ke.key) {
	case OIS::KC_ESCAPE:
		owner->Esc_Key();
		//gm->sendmsg("Esc");
		break;
	case OIS::KC_Q:
		owner->Q_Key();
		break;
	default:
		break;
	}
	
	return true;
}
bool GmInputListener::keyReleased(const OIS::KeyEvent& ke) {
	return false;
}