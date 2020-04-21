#pragma once

#include "Input_OIS_Listener.h"

class GameManager;

class InputListener : public Input_OIS_Listener {
public:
	InputListener(GameManager* ow);
	~InputListener() {};

private:
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	
	GameManager* _owner;
};