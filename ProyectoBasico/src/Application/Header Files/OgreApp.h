#ifndef OGREAPP_H
#define OGREAPP_H


#include "EasyDefines.h"
#include <Ogre.h>

namespace OgreEasy {

	class OgreApp {
	public:
		OgreApp() {};
		~OgreApp() {};
		void AnOgreApplication();
		void createMesh();

	private:
		//Escena
		Ogre::SceneManager* lScene;
		//Nodo "main" de la escena
		Ogre::SceneNode* lRootSceneNode;
		//Root
		Ogre::Root* lRoot;
		//Window
		Ogre::RenderWindow* lWindow;
	};



};

#endif