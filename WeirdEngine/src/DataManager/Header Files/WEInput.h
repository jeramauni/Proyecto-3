#pragma once

#include <InputListener.h>
#include "InputComponent.h"

class WEInputListener : public InputKeyListener {
public:
	WEInputListener(Container *owner);
	~WEInputListener();

	// Teclas
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);

	Container* _owner;
private:

};

class WEInput : public InputComponent {
public:
	WEInput(Container* c);
	~WEInput() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	WEInputListener* getListener();

private:
	WEInputListener* _listener;
};