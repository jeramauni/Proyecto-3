#pragma once
#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btHashMap.h"
#include <vector>
#include <map>
#include <string>

class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;

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
	void basicMesh(void* newNode) {
		//create the new shape, and tell the physics that is a Box
		btCollisionShape* newRigidShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
		collisionShapes.push_back(newRigidShape);
		//getCollisionShapes().push_back(newRigidShape);

		//set the initial position and transform. For this demo, we set the tranform to be none
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setRotation(btQuaternion(1.0f, 1.0f, 1.0f, 0));

		//set the mass of the object. a mass of "0" means that it is an immovable object
		btScalar mass = 0.1f;
		btVector3 localInertia(0, 0, 0);

		startTransform.setOrigin(btVector3(0, 0, 0));
		newRigidShape->calculateLocalInertia(mass, localInertia);

		//actually contruvc the body and add it to the dynamics world
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		body->setRestitution(1);
		body->setUserPointer(newNode);
		//getDynamicsWorld().ste
		dynamicsWorld->addRigidBody(body);
	}
};

