#pragma once
//#include "Component.h"CAMBIO

class Component;

class CompFactory {
public:
	virtual Component* Create() = 0;
};