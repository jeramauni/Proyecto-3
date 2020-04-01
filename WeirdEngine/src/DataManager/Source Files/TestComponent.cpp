#include "TestComponent.h"
#include <iostream>

TestComponent::TestComponent()
{
}

void TestComponent::Init()
{
	f = 0.0;
	for (size_t i = 0; i < 3; i++)
	{
		intArray[i] = 0;
	}
	s = "-1";
	b = false;
}

void TestComponent::Init(const float& f_, const int intArray_[3], const std::string& s_, const bool& b_)
{
	f = f_;
	for (size_t i = 0; i < 3; i++)
	{
		intArray[i] = intArray_[i];
	}
	s = s_;
	b = b_;
}

void TestComponent::Debug()
{
	std::cout << "Float: " << f << '\n';
	std::cout << "String: " << s << '\n';
	std::cout << "Bool: " << b << '\n';
	std::cout << "Int Array: ";
	for (size_t i = 0; i < 3; i++)
	{
		std::cout << intArray[i] << '|';
	}
	std::cout << '\n';
}