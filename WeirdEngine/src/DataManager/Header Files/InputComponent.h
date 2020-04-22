#pragma once

#include "Component.h"
class EntityC;

class InputComponent : public Component {
public:
	InputComponent();
	~InputComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);

private:
	// Puntero a la entidad a la que afecta el input
	EntityC* _entity;
};