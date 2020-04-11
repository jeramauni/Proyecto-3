#ifndef GmInputComponent_H
#define GmInputComponent_H

#include "OISKeyboard.h"
#include "Component.h"
#include "GmInputListener.h"
class GameManager;

class GmInputComponent : public Component {
public:
	GmInputComponent();
	~GmInputComponent();

	void Init() {};
	void Init(GameManager* gm);
	void Q_Key();
	void Esc_Key();
	bool _state = false;
	bool _playing = false;
	GmInputListener* getListener() { return listener; }

private:
	// Puntero al gameManager
	GameManager* _gm;
	GmInputListener* listener;
};

#endif