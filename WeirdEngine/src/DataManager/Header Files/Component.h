#pragma once
#include "Ogre.h"
#include "Messages_decl.h"
#include "Observer.h"

//Factorias
#include <unordered_map>
//Vars Globales
extern std::unordered_map<std::string, CompFactory*> factories;

class Component : public Observer {
public:
	Ogre::String name;
	virtual void Init()=0;
	//virtual void receive(const void* senderObj, const msg::Message& msg)=0;
};

