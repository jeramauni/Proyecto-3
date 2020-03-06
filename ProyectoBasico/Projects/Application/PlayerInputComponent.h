#pragma once

#include "OISKeyboard.h"
#include "Component.h"
#include "EntityC.h"

class PlayerInputComponent : public OIS::KeyListener, public Component
{
public:
	PlayerInputComponent(EntityC* ent);
	~PlayerInputComponent();
	

private:
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);

	// Puntero a la entidad a la que afecta el input
	EntityC* _entity;
};

