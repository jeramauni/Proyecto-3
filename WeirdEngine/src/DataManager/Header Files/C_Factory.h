#pragma once

class Component;

class CompFactory {
public:
	virtual Component* Create() = 0;
};