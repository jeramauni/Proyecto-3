#pragma once
#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btHashMap.h"
#include <Ogre.h>
#include <vector>
#include <map>
#include <string>

class PhysicsEngine
{
private:
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape*> collisionShapes;
	std::map<std::string, btRigidBody*> physicsAccessors;

public:
	void initObjects();
	void floor();
	int basicMesh(Ogre::SceneNode* newNode, btVector3 collSize, bool gravity);
	void planeMesh(Ogre::SceneNode* newNode);
	bool physicsLoop();
};

