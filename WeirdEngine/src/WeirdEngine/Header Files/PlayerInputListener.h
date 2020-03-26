#pragma once

#include "Input_OIS_Listener.h"

class PlayerInputComponent;

class PlayerInputListener : public Input_OIS_Listener
{
public:
	PlayerInputListener(PlayerInputComponent* ow);
	~PlayerInputListener() {};
	bool _state = false;
	bool _playing = false;

private:
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	
	PlayerInputComponent* _owner;
};

