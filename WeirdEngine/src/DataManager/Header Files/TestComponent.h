#pragma once
//***********!ADVERTENCIA¡***********
// Clase utilizada para testear el funcionamiento del proyecto: "DataManager"
//***********************************
#include "Component.h"
#include <string>
class TestComponent :	public Component
{
public:
	TestComponent();
	~TestComponent() {};
	void Init();
	void Init(const float& f_, const int intArray_[3], const std::string& s_, const bool& b_);
	void Debug();

private:
	float f;
	int intArray[3];
	std::string s;
	bool b;
};