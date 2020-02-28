#ifndef OGREAPP_H
#define OGREAPP_H

//#include "OgreString.h"
#include "EasyDefines.h"
#include <Ogre.h>

namespace OgreEasy {

	class OgreApp {
	public:
		OgreApp() {};
		~OgreApp() {};
		void AnOgreApplication();
		void squareGeneration();
		void createSquare(Ogre::String nameOfMesh);
		void meshGeneration();

		void lightGeneration();
		void materialGeneration(Ogre::String lNameOfResourceGroup);

		//Añade una entidad a la escena
		Ogre::SceneNode* addEntityToScene(Ogre::String meshGroup, Ogre::String mesh);
	private:
		//Materials
		Ogre::MaterialPtr noLightMat(Ogre::MaterialManager& matMng, Ogre::String name);
		Ogre::MaterialPtr lightMat(Ogre::MaterialManager& matMng, Ogre::String name);
		Ogre::MaterialPtr noLightTextMat(Ogre::MaterialManager& matMng, Ogre::String name);
		Ogre::MaterialPtr lightTextMat(Ogre::MaterialManager& matMng, Ogre::String name);
		Ogre::MaterialPtr oneMoreMat(Ogre::MaterialManager& matMng, Ogre::String name);

		//Escena
		Ogre::SceneManager* lScene;
		//Nodo "main" de la escena
		Ogre::SceneNode* lRootSceneNode;
		//Root
		Ogre::Root* lRoot;
		//Window
		Ogre::RenderWindow* lWindow;
		//Light
		Ogre::SceneNode* lLightSceneNode;
	};
};

#endif