#pragma once

#include <OISKeyboard.h>

class WEManager;

class InputKeyListener : public OIS::KeyListener {
public:
	InputKeyListener(WEManager* ow);
	~InputKeyListener() {};

private:
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	
	WEManager* _owner;
};