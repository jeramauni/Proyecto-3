#include "PhysicsComponent.h"
#include "ComponentFactory.h"
#include <messages_defs.h>

DEFINE_FACTORY(Physics);

PhysicsComponent::PhysicsComponent() {
	_name = "Physics";
	id = -1;
}

PhysicsComponent::~PhysicsComponent() {
	id = NULL;
}

void PhysicsComponent::Init(std::unordered_map<std::string, std::string>& param)
{
	//Aux
	std::vector<std::string> aux;

	//Gravity
	if (param.at("gravity") == "true")
		gravity = true;
	else
		gravity = false;

	//CollSize
	aux = GetWords(param.at("collSize"));
	collSize = btVector3(std::stof(aux[0]), 
						 std::stof(aux[1]), 
						 std::stof(aux[2]));

	
}

void PhysicsComponent::update(Container* c, float time) {

}

void PhysicsComponent::receive(Container* c, const msg::Message& msg) {
	switch (msg.type_) {
	case msg::PRUEBA:
		
		break;
	default:
		break;
	}
}

int PhysicsComponent::GetID()
{
	return id;
}

void PhysicsComponent::SetID(int newID) {
	id = newID;
}

btVector3 PhysicsComponent::GetScale()
{
	return collSize;
}

bool PhysicsComponent::HaveGravity()
{
	return gravity;
}