#pragma once
#include "Component.h"
static class ComponentFactory
{
	Component* Create() {
		return new Component();
	};
};

