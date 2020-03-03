#ifndef OGREAPP_H
#define OGREAPP_H

#include "InputManager.h"
#include "EasyDefines.h"
#include "InitOgre.h"
#include <Ogre.h>


//Temporal
#include "OneKeyComponent.h"

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

		//Getters
		Ogre::Root* getRoot() { return lRoot; }
		Ogre::RenderWindow* getWindow() { return lWindow; }

		//Añade una entidad a la escena
		Ogre::SceneNode* addEntityToScene(Ogre::String mesh);
	private:
		bool shutDown = false;

		//Temp
		OneKeyComponent *okc;

		//Materials -> Al cargarlos desde scripts en resources/textures ya no hacen falta estos metodos
		Ogre::MaterialPtr noLightMat(Ogre::MaterialManager& matMng, Ogre::String name);
		Ogre::MaterialPtr lightMat(Ogre::MaterialManager& matMng, Ogre::String name);
		Ogre::MaterialPtr noLightTextMat(Ogre::MaterialManager& matMng, Ogre::String name);
		Ogre::MaterialPtr lightTextMat(Ogre::MaterialManager& matMng, Ogre::String name);
		Ogre::MaterialPtr oneMoreMat(Ogre::MaterialManager& matMng, Ogre::String name);

		//Input Mng
		InputManager *mInputManager;

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