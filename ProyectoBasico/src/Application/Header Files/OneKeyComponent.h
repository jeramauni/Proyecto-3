#ifndef OneKeyComponent_H
#define OneKeyComponent_H

#include "OISKeyboard.h"

class OneKeyComponent : public OIS::KeyListener {
public:
	bool state = false;
private:
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);
};


#endif