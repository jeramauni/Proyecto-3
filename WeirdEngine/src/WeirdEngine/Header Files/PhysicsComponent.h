#pragma once
#include "Component.h"

#include "Utilities/Vector3.h"
#include <string>

class PhysicsEngine;
class Container;

namespace msg {
	struct Message;
}

class PhysicsComponent : public Component {
public:
	PhysicsComponent(Container* e);
	~PhysicsComponent();
	
	void Init(std::unordered_map<std::string, std::string>& param);

	// Es necesaria para actualizar la pos
	void update(Container* c, float time);

	//Receive implementation
	void receive(Container* c, const msg::Message& msg);

	int GetID();
	Vector3 GetScale();
	bool HaveGravity();

	void move(Vector3 dir);
	void jump(Vector3 dir);

private:
	bool gravity;
	int id;
	Vector3 collSize;
	PhysicsEngine* _py;
};

