#ifndef GmInputComponent_H
#define GmInputComponent_H

#include "OISKeyboard.h"

class GameManager;

class GmInputComponent : public OIS::KeyListener {
public:
	GmInputComponent(GameManager *gm);
	~GmInputComponent();

	bool _state = false;
	bool _playing = false;

private:
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);
	
	// Puntero al gameManager
	GameManager* _gm;
};

#endif