#pragma once

#include "Messages_decl.h"
#include "Observer.h"
#include <string>
#include <unordered_map>



class Component : public Observer {
public:
	std::string name;
	virtual void Init(std::unordered_map<std::string, std::string>& param) = 0;
protected:
	std::vector<std::string> GetWords(std::string& s);

	//virtual void receive(const void* senderObj, const msg::Message& msg)=0;
};

