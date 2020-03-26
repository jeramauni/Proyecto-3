#include "OgreApp.h";

// I will use std::auto_ptr so I need to include 'memory'. 
#include <memory>
// I will check for std::exception.
#include <exception>

//Here I include my other files
#include "RenderUtilities.h"
#include "InitOgre.h"

#include "EntityC.h"
#include "RenderComponent.h";

namespace OgreEasy {

	OgreApp::OgreApp() {
		// Init Ogre
		lOgreInit = new OgreEasy::SimpleOgreInit();
		lOgreInit->initOgre();
	}

	OgreApp::~OgreApp() {
		//OIS::InputManager::destroyInputSystem(mInputMng);
	}

	// Funcion para iniciar la app de Ogre
	void OgreApp::AnOgreApplication() {

		// Tener las variables principales a mano
		lRoot = lOgreInit->mRoot.get();
		lWindow = lOgreInit->mWindow;

		// SceneManager
		lScene = lRoot->createSceneManager();

		// SceneNode
		lRootSceneNode = lScene->getRootSceneNode();

		//--------------------------- CAMARA Y VIEWPORT ---------------------------
		// Camera
		Ogre::Camera* lCamera = lScene->createCamera("Camera1");

		// Attach the camera to an scene node. Makes it easier to move it in the scene
		Ogre::SceneNode* lCameraNode = lRootSceneNode->createChildSceneNode("CameraNode1");
		lCameraNode->attachObject(lCamera);

		/*
		Creamos el viewport que es el link entre el 1 camara y una superficie de dibujado.
		Puedes tener varios vp en una ventana.
		Si le ponemos en autoUpdate cuando se actualize la ventana el vp se dibujara.
		*/
		float lViewportWidth = 0.88f;
		float lViewportHeight = 0.88f;
		float lViewportLeft = (1.0f - lViewportWidth) * 0.5f;
		float lViewportTop = (1.0f - lViewportHeight) * 0.5f;
		unsigned short lMainViewportZOrder = 100;
		Ogre::Viewport* vp = lWindow->addViewport(lCamera, lMainViewportZOrder, lViewportLeft, lViewportTop, lViewportWidth, lViewportHeight);

		// I want the viewport to draw the scene automatically, when I will call lWindow->update();
		vp->setAutoUpdated(true);

		// Color for the viewPort
		vp->setBackgroundColour(Ogre::ColourValue(1, 0, 1));

		// I choose the visual ratio of the camera. To make it looks real, I want it the same as the viewport. 
		float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
		lCamera->setAspectRatio(ratio);

		
		//If (far/near)>2000 then you will likely get 'z fighting' issues.
		lCamera->setNearClipDistance(1.5f);
		lCamera->setFarClipDistance(3000.0f);

		//--------------------------- WINDOW ---------------------------
		// Active the window
		lWindow->setActive(true);

		// I want to update myself the content of the window, not automatically
		lWindow->setAutoUpdated(false);

		/*
		cleaning of windows events managed by Ogre::WindowEventUtilities::...
		I call it after a 'pause in window updating', in order to maintain smoothness.
		Explanation : if you clicked 2000 times when the windows was being created, there are
		at least 2000 messages created by the OS to listen to. This is made to clean them.
		*/
		lRoot->clearEventTimes();
		
		return;
	};

	void OgreApp::SceneCleaner() {
		lScene->destroyAllEntities();
	}
	
	// Devuelve un puntero al Nodo de la escena de la entidad
	Ogre::SceneNode* OgreApp::addEntityToScene(Ogre::String mesh) {
		//Entidad
		Ogre::Entity* lEntity = lScene->createEntity(mesh + ".mesh");

		// Le damos el material cargado desde el script
		lEntity->setMaterialName(mesh);
		//Generamos los materiales
		//Le damos el material a la mesh
		//lEntity->setMaterial(lightTextMat(Ogre::MaterialManager::getSingleton(), meshGroup + " Mat"));

		//Nodo
		Ogre::SceneNode* lNode = lRootSceneNode->createChildSceneNode();
		lNode->attachObject(lEntity);

		// Mover el nodo para que lo vea la camara
		float lPositionOffset = float(1 * 2) - (float(1));
		lPositionOffset = lPositionOffset * 20;
		lNode->translate(lPositionOffset, lPositionOffset, -600.0f);
		lNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));

		return lNode;
	}
	
	void OgreApp::lightGeneration() {
		// Iniciamos la luz y se la añadimos a la escena en un nodo
		lLightSceneNode = NULL;
		{
			Ogre::Light* lLight = lScene->createLight();

			// I can set some attributes of the light.
			// The basic light type can be : 
			//		pointlight (like a candle?)
			//		spotlight (kind of 'conic' light)
			//		directional light (like the sun in an outdoor scene).
			// Directional light is like parallel rays coming from 1 direction.
			lLight->setType(Ogre::Light::LT_DIRECTIONAL);

			// Color para la luz. Entre 0.0 y 1.0
			// Diffuse -> color principal de la luz
			// Specular -> color de la luz reflejado
			// El color final de un objeto tambien depende del material
			lLight->setDiffuseColour(0.8f, 0.3f, 0.3f); // this will be a red light
			lLight->setSpecularColour(1.0f, 1.0f, 1.0f);// color of 'reflected' light

			lLightSceneNode = lRootSceneNode->createChildSceneNode();
			lLightSceneNode->attachObject(lLight);
		}

		// Color ambiente
		Ogre::ColourValue lAmbientColour(0.2f, 0.2f, 0.2f, 1.0f);
		lScene->setAmbientLight(lAmbientColour);
	}


	//---------------------------------MATERIALS---------------------------------
	// Metodo para generar los diferentes grupos de donde cogeremos los materiales
	void OgreApp::materialGeneration(Ogre::String lNameOfResourceGroup) {
		//Referencia al materialManager
		Ogre::MaterialManager& lMaterialManager = Ogre::MaterialManager::getSingleton();

		// Cargar un directorio con texturas
		{
			Ogre::ResourceGroupManager& lRgMgr = Ogre::ResourceGroupManager::getSingleton();
			lRgMgr.createResourceGroup(lNameOfResourceGroup);
		
			// Direccion del directorio de las texturas
			Ogre::String lDirectoryToLoadTextures = "resources/textures";
			bool lIsRecursive = false;
			lRgMgr.addResourceLocation(lDirectoryToLoadTextures, "FileSystem", lNameOfResourceGroup, lIsRecursive);

			// Iniciamos los scripts del directorio
			//lRgMgr.initialiseResourceGroup(lNameOfResourceGroup);
			lRgMgr.initialiseAllResourceGroups();

			// Cargamos los archivos que puedan ser cargados
			lRgMgr.loadResourceGroup(lNameOfResourceGroup);
		}
	}

	//------------------------------------- CLOSE ---------------------------------------------
	// I wait until the window is closed.
	// The "message pump" thing is something you will see in most GUI application.
	// It allow the binding of messages between the application and the OS.
	// These messages are most of the time : keystroke, mouse moved, ... or window closed.
	// If I don't do this, the message are never caught, and the window won't close.
	bool OgreApp::RenderLoop() {
		bool f;
		if (!lWindow->isClosed()) {
			// Actualizado de la escena

			// Rotacion de la luz
			Ogre::Degree lAngle(2.5);
			lLightSceneNode->yaw(lAngle);

			// Drawings
			// La ventana hace el update. Los viewport que tengan "autoupdated" activado se dibujaran otra vez en este frame,
			// en el orden dado por la coord z.
			lWindow->update(false);

			// Dibujamos el buffer actualizado
			bool lVerticalSynchro = true;
			lWindow->swapBuffers();

			// This update some internal counters and listeners.
			// Each render surface (window/rtt/mrt) that is 'auto-updated' has got its 'update' function called.
			lRoot->renderOneFrame();

			// Llamar a esto con handleInput
			if(shutDown) lWindow->destroy();

			Ogre::WindowEventUtilities::messagePump();
			f = true;
		}
		else f = false;
		return f;
	}
}