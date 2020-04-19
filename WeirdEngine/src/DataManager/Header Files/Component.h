#pragma once
#include "Ogre.h"
#include "Messages_decl.h"
#include "Observer.h"



class Component : public Observer {
public:
	Ogre::String name;
	virtual void Init()=0;
	//virtual void receive(const void* senderObj, const msg::Message& msg)=0;
};

