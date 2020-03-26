#pragma once

#define CREATE_FACTORY(x) class x##Factory {public: x##Component* Create(){ return new x##Component();}}



class Component
{
	virtual void Init()=0;
};

