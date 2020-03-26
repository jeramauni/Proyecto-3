#pragma once
#include "OISKeyboard.h"

class Input_OIS_Listener: public::OIS::KeyListener
{
public:
	Input_OIS_Listener() {};
private:
	virtual bool keyPressed(const OIS::KeyEvent& ke)=0;
	virtual bool keyReleased(const OIS::KeyEvent& ke)=0;
};

