#ifndef PlayerInputComponent_H
#define PlayerInputComponent_H

#include "Component.h"
#include "PlayerInputListener.h"


class EntityC;

class PlayerInputComponent : public Component {
public:
	PlayerInputComponent();
	~PlayerInputComponent();

	void Init() {};
	void Init(EntityC* ent);
	PlayerInputListener* getListener();

private:
	// Puntero a la entidad a la que afecta el input
	EntityC* _entity;
	PlayerInputListener* _listener;
};

#endif