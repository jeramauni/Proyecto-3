#include "PhysicsComponent.h"
#include "ComponentFactory.h"
DEFINE_FACTORY(Physics);

PhysicsComponent::PhysicsComponent()
{
	name = "Physics";
}

PhysicsComponent::~PhysicsComponent()
{
	id = NULL;
}
void PhysicsComponent::Init(std::unordered_map<std::string, std::string>& param)
{
	std::vector<std::string> aux = GetWords(param.at("gravity"));
	if (std::stof(aux[0]) == 0) gravity = false;
	else gravity = true;
	aux.clear();

	aux = GetWords(param.at("collSize"));
	collSize = btVector3(std::stof(aux[0]), 
						 std::stof(aux[1]), 
						 std::stof(aux[2]));
	aux.clear();
}
int PhysicsComponent::GetID()
{
	return id;
}

void PhysicsComponent::SetID(int newID)
{
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
