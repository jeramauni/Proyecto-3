#ifndef PlayerInputComponent_H
#define PlayerInputComponent_H

#include "OISKeyboard.h"
#include "Component.h"

class EntityC;

class PlayerInputComponent : public OIS::KeyListener, public Component {
public:
	PlayerInputComponent();
	~PlayerInputComponent();

	void Init() {};
	void Init(EntityC* ent);

private:
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);

	// Puntero a la entidad a la que afecta el input
	EntityC* _entity;
};

#endif