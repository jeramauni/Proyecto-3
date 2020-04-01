#pragma once
#include "Input_OIS_Listener.h"

class GmInputComponent;

class GmInputListener: public Input_OIS_Listener {
public:
	GmInputListener(GmInputComponent* ow);
	~GmInputListener() {};
	bool _state = false;
	bool _playing = false;
private:
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	GmInputComponent* owner;
};

