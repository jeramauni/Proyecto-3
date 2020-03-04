#ifndef OGREAPP_H
#define OGREAPP_H

#include "EasyDefines.h"
#include "InitOgre.h"
#include <Ogre.h>

namespace OgreEasy {

	class OgreApp {
	public:
		// Constructrora
		OgreApp();
		~OgreApp();

		//Main
		void AnOgreApplication();

		// Meshes
		void squareGeneration();
		void createSquare(Ogre::String nameOfMesh);
		void meshGeneration();

		//Luz
		void lightGeneration();
		//Material
		void materialGeneration(Ogre::String lNameOfResourceGroup);
		//Métodos para el GameManager
		void SceneCleaner();
		bool RenderLoop();

		//Apagado de Ogre
		void turnOff() { shutDown = true; }

		//Getters
		Ogre::Root* getRoot() { return lRoot; }
		Ogre::RenderWindow* getWindow() { return lWindow; }

		//Añade una entidad a la escena
		Ogre::SceneNode* addEntityToScene(Ogre::String mesh);
	private:
		// Para fin de la escena
		bool shutDown = false;

		//App de Ogre
		OgreEasy::SimpleOgreInit* lOgreInit;
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