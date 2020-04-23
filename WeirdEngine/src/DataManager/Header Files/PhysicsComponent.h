#pragma once
#include "Component.h"

#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btHashMap.h"
#include <Ogre.h>
#include <string>

class PhysicsComponent : public Component {

public:
	PhysicsComponent();
	~PhysicsComponent();

	void Init(std::unordered_map<std::string, std::string>& param);

	// Implementar la que sea necesaria
	void update(Container* c, float time) {};
	void handleInput(Container* c, float time) {};

	//Receive implementation
	void receive(Container* c, const msg::Message& msg) {};

	int GetID();
	void SetID(int newID);
	btVector3 GetScale();
	bool HaveGravity();

private:
	bool gravity;
	int id;
	btVector3 collSize;
};

