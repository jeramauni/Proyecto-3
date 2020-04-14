#pragma once
#include "Component.h"
class CompFactory {
public:
	virtual Component* Create() = 0;
};