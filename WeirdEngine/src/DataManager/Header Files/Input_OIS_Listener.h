#pragma once
#include "OISKeyboard.h"
#include "OISMouse.h"

class Input_OIS_Listener: public::OIS::KeyListener
{
public:
	Input_OIS_Listener() {};
private:
	virtual bool keyPressed(const OIS::KeyEvent& ke)=0;
	virtual bool keyReleased(const OIS::KeyEvent& ke)=0;
	virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id) = 0;
};