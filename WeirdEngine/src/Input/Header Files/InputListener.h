#pragma once

#include <OIS.h>

// Input Listener class to be used as callback class for InputManager
// Abstract class
// Handles Input events

class InputListener : public OIS::KeyListener, public OIS::MouseListener {
public:
	InputListener() {};
	~InputListener() {};

	// Teclas
	virtual bool keyPressed(const OIS::KeyEvent& ke) = 0;
	virtual bool keyReleased(const OIS::KeyEvent& ke) = 0;

	// Raton
	virtual bool mouseMoved(const OIS::MouseEvent& me) = 0;
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id) = 0;
	virtual bool mouseRelease(const OIS::MouseEvent& me, OIS::MouseButtonID id) = 0;

private:
	
};