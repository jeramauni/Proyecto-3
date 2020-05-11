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
public:
	struct bulletObject {
	public:
		int id;
		bool hit;
		btRigidBody* body;
		btVector3 size;
		bulletObject(btRigidBody* b, int i) : body(b), id(i), hit(false) {};
		void setHit(bool _hit)
		{
			hit = _hit;
		}
		bool getHit()
		{
			return hit;
		};
	};
	void initObjects();
	int basicMesh(Ogre::SceneNode* newNode, btVector3 collSize, bool gravity);
	void addForce(int id, btVector3 fDirection);
	void changeVelocity(int id, btVector3 vDirection);
	bool isColliding(int id);
	bool physicsLoop();

private:
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape*> collisionShapes;
	std::map<std::string, btRigidBody*> physicsAccessors;
	std::list<bulletObject> bulletOBs;
};

