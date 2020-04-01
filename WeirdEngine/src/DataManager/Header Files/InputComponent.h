#ifndef InputComponent_H
#define InputComponent_H

#include "Component.h"
//#include "InputListener.h"

class EntityC;

class InputComponent : public Component {
public:
	InputComponent();
	~InputComponent();

	void Init() {};
	void Init(EntityC* ent);
	//InputListener* getListener();

private:
	// Puntero a la entidad a la que afecta el input
	EntityC* _entity;
	//InputListener* _listener;
};

#endif