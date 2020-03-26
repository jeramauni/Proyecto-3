#include "PhysicsEngine.h"

void PhysicsEngine::initObjects()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
}

void PhysicsEngine::floor()
{
	//create the plane entity to the physics engine, and attach it to the node

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -50, 0));

	btScalar groundMass(0.); //the mass is 0, because the ground is immovable (static)
	btVector3 localGroundInertia(0, 0, 0);

	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(groundTransform);

	groundShape->calculateLocalInertia(groundMass, localGroundInertia);

	btRigidBody::btRigidBodyConstructionInfo groundRBInfo(groundMass, groundMotionState, groundShape, localGroundInertia);
	btRigidBody* groundBody = new btRigidBody(groundRBInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(groundBody);
}

void PhysicsEngine::basicMesh(Ogre::SceneNode* newNode)
{
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

bool PhysicsEngine::frameStarted()
{
	if (this != NULL) {
		dynamicsWorld->stepSimulation(1.0f / 60.0f); //suppose you have 60 frames per second

		for (int i = 0; i < collisionShapes.size(); i++) {
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);

			if (body && body->getMotionState()) {
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);

				void* userPointer = body->getUserPointer();
				if (userPointer) {
					btQuaternion orientation = trans.getRotation();
					Ogre::SceneNode* sceneNode = static_cast<Ogre::SceneNode*>(userPointer);
					sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
					sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
				}
			}
		}
	}
	return true;
}