#pragma once

#include "Component.h"
#include <InputListener.h>

class WEInput : public Component, public InputListener {
public:
	WEInput();
	~WEInput() {};
	void Init(std::unordered_map<std::string, std::string>& param);

	// Teclas
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);

private:
};