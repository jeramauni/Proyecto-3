#ifndef GmInputComponent_H
#define GmInputComponent_H

#include "OISKeyboard.h"
#include "Component.h"

class GameManager;

class GmInputComponent : public OIS::KeyListener, public Component {
public:
	GmInputComponent();
	~GmInputComponent();

	void Init() {};
	void Init(GameManager* gm);

	bool _state = false;
	bool _playing = false;

private:
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);
	
	// Puntero al gameManager
	GameManager* _gm;
};

#endif