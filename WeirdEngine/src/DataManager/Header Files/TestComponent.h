#pragma once
//***********!ADVERTENCIA¡***********
// Clase utilizada para testear el funcionamiento del proyecto.
//***********************************
#include "Component.h"
#include <string>
class TestComponent :	public Component
{
public:
	TestComponent();
	~TestComponent() {};
	void Init(std::unordered_map<std::string, std::string>& param);
	void Debug();

private:
	float f;
	int intArray[3];
	std::string s;
	bool b;
};