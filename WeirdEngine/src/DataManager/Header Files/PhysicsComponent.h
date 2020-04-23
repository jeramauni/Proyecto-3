#pragma once
#include "Component.h"

#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btHashMap.h"
#include <Ogre.h>
#include <vector>
#include <map>
#include <string>

class PhysicsComponent : public Component {

public:
	PhysicsComponent();
	~PhysicsComponent();

	void Init(std::unordered_map<std::string, std::string>& param);

	int GetID();
	void SetID(int newID);
	btVector3 GetScale();
	bool HaveGravity();

private:
	bool gravity;
	int id = -1;
	btVector3 collSize;
};

