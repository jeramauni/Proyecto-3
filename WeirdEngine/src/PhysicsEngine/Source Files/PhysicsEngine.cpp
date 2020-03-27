#include "PhysicsEngine.h"
#include <iostream>

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

	startTransform.setOrigin(btVector3(newNode->getPosition().x, newNode->getPosition().y, newNode->getPosition().z));
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

bool PhysicsEngine::physicsLoop()
{
	if (this != NULL) {
		//PRIMERA FORMA
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
					std::cout << sceneNode->getPosition();
					sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
				}
			}
		}

		//SEGUNDA FORMA
			// Update the dynamic world
	// This automatically performs collision detection and physics simulation
	//// It also updates the world transform for all the active objects
	//	dynamicsWorld->stepSimulation(1.0f / 60.0f);

	//	// Link the data in Physics and Render engines
	//	for (int i = 0; i < collisionShapes.size(); i++)
	//	{
	//		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
	//		btRigidBody* rb = btRigidBody::upcast(obj);

	//		if (rb && rb->getMotionState())
	//		{
	//			Ogre::SceneNode* n = static_cast<Ogre::SceneNode*>(rb->getUserPointer());
	//			btVector3 rbPos = rb->getCenterOfMassPosition();
	//			btQuaternion rbRot = rb->getOrientation();
	//			Ogre::Vector3 nPos(rbPos.x(), rbPos.y(), rbPos.z());
	//			Ogre::Quaternion nRot(rbRot.w(), rbRot.x(), rbRot.y(), rbRot.z());
	//			n->setPosition(nPos);
	//			std::cout << n->getPosition() << '\n';
	//			n->setOrientation(nRot);
	//		}
	//	}

		// Proccess all the collisions
	//	detectCollisions();

	}
	return true;
}