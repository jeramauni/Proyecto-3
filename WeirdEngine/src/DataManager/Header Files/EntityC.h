#pragma once

#include "Observer.h"

#include <OgreSceneNode.h>
#include <WEManager.h>

class EntityC : public Observer {
public:
	EntityC(std::string name, WEManager* wem);
	virtual ~EntityC();

	// Manager
	WEManager* getGame() const;
	void setGame(WEManager* game);

	// Setter/getter Node
	void setNode(Ogre::SceneNode* node);
	Ogre::SceneNode* getNode();

	// Posicion
	Ogre::Vector3 getPosition() const;
	void setPos(const Ogre::Vector3& p);

	// Activar/Desactivar
	void setActive(bool sw);
	bool isActive();

	virtual void receive(const void* senderObj, const msg::Message& msg);

	// some GameObjects cannot be initialized in the constructor,
	// for example when we create them using the default constructor
	// and without passing the game. This method is supposed to
	// be called once they are ready to be initialized. The
	// default implementation does nothing.
	virtual void init();

	//Lo implementan aquellas entidades que lo necesiten
	virtual void update(float time) = 0;

private:
	// Puntero al nodo de la escena
	Ogre::SceneNode* _Node = nullptr;

	std::string _entName;

	// Puntero al motor
	WEManager* _weM;

	// Inidica si la entidad esta activa
	bool _active;
};