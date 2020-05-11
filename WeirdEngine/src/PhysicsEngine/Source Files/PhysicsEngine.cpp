#include "PhysicsEngine.h"
#include <iostream>

void PhysicsEngine::initObjects()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	//bool callbackFunc(btManifoldPoint & cp, const btCollisionObjectWrapper * colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper * colObj1Wrap, int partId1, int index1);
	//gContactAddedCallback = callbackFunc;
}
//
//bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
//{
//	//PhysicsEngine::bulletObject* btOB = ((PhysicsEngine::bulletObject*)colObj0Wrap->getCollisionObject()->getUserPointer());//static_cast<PhysicsEngine::bulletObject*>(userPointer);
//	//std::cout << "HIT!!" << std::endl;
//	//btOB->setHit(true);
//	
//	//static_cast<PhysicsEngine::bulletObject*>(colObj0Wrap->getCollisionObject()->getUserPointer())->setHit(true);
//	//((PhysicsEngine::bulletObject*)colObj0Wrap->getCollisionObject()->getUserPointer())->setHit(true);
//	return false;
//}

int PhysicsEngine::basicMesh(Ogre::SceneNode* newNode, btVector3 collSize, bool gravity)
{
	//create the new shape, and tell the physics that is a Box
	//btCollisionShape* newRigidShape = new btBoxShape(collSize);
	btCollisionShape* newRigidShape = new btBoxShape(btVector3(newNode->getScale().x, newNode->getScale().y, newNode->getScale().z));
	collisionShapes.push_back(newRigidShape);
	//getCollisionShapes().push_back(newRigidShape);
	btRigidBody* body = nullptr;
	bulletObject newBO = bulletObject(body, 0);
	newBO.size = btVector3(newNode->getScale().x, newNode->getScale().y, newNode->getScale().z);
	//set the initial position and transform. For this demo, we set the tranform to be none
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(newNode->getOrientation().x, newNode->getOrientation().y, newNode->getOrientation().z, newNode->getOrientation().w));

	//set the mass of the object. a mass of "0" means that it is an immovable object
	btScalar mass;
	if (gravity) mass = 10.1f;
	else mass = 0.0f; //the mass is 0, because the ground is immovable (static)
	btVector3 localInertia(0, 0, 0);

	startTransform.setOrigin(btVector3(newNode->getPosition().x, newNode->getPosition().y, newNode->getPosition().z));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	//actually contruvc the body and add it to the dynamics world
	btDefaultMotionState* myMotionState;
	//btRigidBody* body;
	if (gravity) {
		myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);
		newBO.body = new btRigidBody(rbInfo);
		newBO.body->setRestitution(1);
		newBO.body->setUserPointer(newNode);

		dynamicsWorld->addRigidBody(newBO.body);
	}
	else {
		btCollisionShape* groundShape = new btBoxShape(collSize);
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(startTransform);
		btVector3 localGroundInertia(0, 0, 0);
		groundShape->calculateLocalInertia(mass, localGroundInertia);
		btRigidBody::btRigidBodyConstructionInfo groundRBInfo(mass, groundMotionState, groundShape, localGroundInertia);
		newBO.body = new btRigidBody(groundRBInfo);
		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(newBO.body);
	}
	newBO.body->setCollisionFlags(newBO.body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	newBO.id = dynamicsWorld->getNumCollisionObjects() - 1;
	bulletOBs.push_back(newBO);
	return dynamicsWorld->getNumCollisionObjects() - 1;
}

void PhysicsEngine::addForce(int id, btVector3 fDirection)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[id];
	btRigidBody* body = btRigidBody::upcast(obj);
	if(std::abs(body->getLinearVelocity().y()) <= 1.0f)	body->applyCentralImpulse(fDirection);
}

void PhysicsEngine::changeVelocity(int id, btVector3 vDirection)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[id];
	btRigidBody* body = btRigidBody::upcast(obj);
	body->setLinearVelocity(btVector3(vDirection.x(), body->getLinearVelocity().y(), vDirection.z()));
	body->activate();
}

bool PhysicsEngine::isColliding(int id)
{
	bulletObject btOb0 = bulletObject(nullptr, 0);
	bool searching = true;
	bool colliding = false;
	std::list<bulletObject>::iterator it = bulletOBs.begin();
	while (searching && it != bulletOBs.end())
	{
		if ((*it).id == id)
		{
			searching = false;
			btOb0 = (*it);
			float size_x = btOb0.size.getX() * 25;
			//std::cout << "Tamaño X: " << size_x << std::endl;
			float size_y = btOb0.size.getY() * 25;
			//std::cout << "Tamaño Y: " << size_y << std::endl;
			float size_z = btOb0.size.getZ() * 25;
			//std::cout << "Tamaño Z: " << size_z << std::endl;
			btTransform f;
			btVector3 s;
			btVector3 d;
			btOb0.body->getCollisionShape()->getAabb(f, s, d);
			int pruebas = 0;
			btTransform trans;
			btOb0.body->getMotionState()->getWorldTransform(trans);
			std::list<bulletObject>::iterator coll = bulletOBs.begin();
			while (coll != bulletOBs.end() && !colliding)
			{
				if ((*coll).id == btOb0.id) ++coll;
				btTransform trans_coll;
				(*coll).body->getMotionState()->getWorldTransform(trans_coll);
				float distX = std::abs(trans.getOrigin().getX() - trans_coll.getOrigin().getX()) - (*coll).size.getX() * 25;
				if (distX <= (size_x + 1))
				{
					float distY = std::abs(trans.getOrigin().getY() - trans_coll.getOrigin().getY()) - (*coll).size.getY() * 25;
					if (distY <= (size_y + 1))
					{
						float distZ = std::abs(trans.getOrigin().getZ() - trans_coll.getOrigin().getZ()) - (*coll).size.getZ() * 25;
						if (distZ <= (size_z + 1))
						{
							colliding = true;
						}
					}
				}
				++coll;
			}
			//for (std::list<bulletObject>::iterator coll = bulletOBs.begin(); coll != bulletOBs.end(); ++coll)
			//{
			//	if ((*coll).id == btOb0.id) ++coll;
			//	btTransform trans_coll;
			//	(*coll).body->getMotionState()->getWorldTransform(trans_coll);
			//	float distX = std::abs(trans.getOrigin().getX() - trans_coll.getOrigin().getX()) - (*coll).size.getX() * 25;
			//	std::cout << "Distancia en X con ["<< pruebas <<"]: " << distX << std::endl;
			//	if (distX <= (size_x + 1))
			//	{
			//		float distY = std::abs(trans.getOrigin().getY() - trans_coll.getOrigin().getY()) - (*coll).size.getY() * 25;
			//		std::cout << "Distancia en Y con [" << pruebas << "]: " << distY << std::endl;
			//		if (distY <= (size_y + 1))
			//		{
			//			float distZ = std::abs(trans.getOrigin().getZ() - trans_coll.getOrigin().getZ()) - (*coll).size.getZ() * 25;
			//			std::cout << "Distancia en Z con [" << pruebas << "]: " << distZ << std::endl;
			//			if (distZ <= (size_z + 1))
			//			{
			//				colliding = true;
			//			}
			//		}
			//	}
			//	++pruebas;
			//}
		}
		++it;
	}
	return colliding;
}

bool PhysicsEngine::physicsLoop()
{
	if (this != NULL) {
		//PRIMERA FORMA
		dynamicsWorld->stepSimulation(120.0f / 60.0f); //suppose you have 60 frames per second

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
					//std::cout << sceneNode->getPosition() << "\n";
					//sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
				}
			}
		}

	}
	return true;
}
