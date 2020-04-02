#pragma once
#include "Ogre.h"

#define CREATE_FACTORY(x) class x##Factory {public: x##Component* Create(){ return new x##Component();}}

class Component {
public:
	Ogre::String name;
	virtual void Init()=0;
};

