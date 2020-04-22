#pragma once
#include "Messages_decl.h"
#include "Observer.h"

#include <string>

class Component : public Observer {
public:
	std::string name;
	virtual void Init()=0;
	//virtual void receive(const void* senderObj, const msg::Message& msg)=0;
};