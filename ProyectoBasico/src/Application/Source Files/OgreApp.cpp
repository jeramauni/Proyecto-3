#include "OgreApp.h";

// I will use std::auto_ptr so I need to include 'memory'. 
#include <memory>
// I will check for std::exception.
#include <exception>

// Includes necesarios
//#include <OgreRoot.h>
//#include <OgreRenderWindow.h>
//Tambien el del viewport k no se cual es :(

//Podemos llamar a Ogre.h directamente e incluiriamos estas y mas


//Here I include my other files
#include "RenderUtilities.h"
#include "InitOgre.h"
#include "EasyDefines.h"

namespace OgreEasy {

	// I declare a function in which I will make my whole application.
	// This is easy then to add more things later in that function.
	// The main will call this function and take care of the global try/catch.
	void OgreApp::AnOgreApplication() {
		// I construct my object that will allow me to initialise Ogre easily.
		OgreEasy::SimpleOgreInit lOgreInit;

		if (!lOgreInit.initOgre()) {
			MWARNING("Impossible to init Ogre correctly.");
			return;
		}

		// Tener las variables principales a mano
		lRoot = lOgreInit.mRoot.get();
		lWindow = lOgreInit.mWindow;

		// SceneManager
		lScene = lRoot->createSceneManager();
		// Deberia funcionar esta inicializacion pero la da como obsoleta ¿?
		//Ogre::SceneManager* lScene = lRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");

		/*
		The 'root SceneNode' is the only scenenode at the beginning in the SceneManager.
		The SceneNodes can be seen as 'transformation' containers <=> it contains scale/position/rotation
		of the objects. There is only 1 root scenenode, and all other scenenode are
		its direct or indirect children.
		*/
		lRootSceneNode = lScene->getRootSceneNode();

		//--------------------------- CAMARA Y VIEWPORT ---------------------------
		// Camera
		Ogre::Camera* lCamera = lScene->createCamera("Camera1");

		// Attach the camera to an scene node. Makes it easier to move it in the scene
		Ogre::SceneNode* lCameraNode = lRootSceneNode->createChildSceneNode("CameraNode1");
		lCameraNode->attachObject(lCamera);

		/*
		We create a viewport on a part of the window.
		A viewport is the link between 1 camera and 1 drawing surface (here the window).
		I can then call 'update();' on it to make it draw the Scene from the camera.
		You can have several viewports on 1 window.
		Check API for details on parameters.
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

		/*
		I choose the clipping far& near planes. if far/near>2000, you can get z buffer problem.
		eg : far/near = 10000/5 = 2000 . it's ok.
		If (far/near)>2000 then you will likely get 'z fighting' issues.
		*/
		lCamera->setNearClipDistance(1.5f);
		lCamera->setFarClipDistance(3000.0f);

		//--------------------------- WINDOW ---------------------------
		// Active the window
		lWindow->setActive(true);

		// I want to update myself the content of the window, not automatically
		lWindow->setAutoUpdated(false);

		//--------------------------- MESH ---------------------------
		createMesh();

		/*
		cleaning of windows events managed by Ogre::WindowEventUtilities::...
		I call it after a 'pause in window updating', in order to maintain smoothness.
		Explanation : if you clicked 2000 times when the windows was being created, there are
		at least 2000 messages created by the OS to listen to. This is made to clean them.
		*/
		lRoot->clearEventTimes();

		//------------------------------------- CLOSE ---------------------------------------------
		// I wait until the window is closed.
		// The "message pump" thing is something you will see in most GUI application.
		// It allow the binding of messages between the application and the OS.
		// These messages are most of the time : keystroke, mouse moved, ... or window closed.
		// If I don't do this, the message are never caught, and the window won't close.
		while (!lOgreInit.mWindow->isClosed()) {

			// Drawings
			// the window update its content.
			// each viewport that is 'autoupdated' will be redrawn now,
			// in order given by its z-order.
			lWindow->update(false);

			// The drawn surface is then shown on the screen
			// (google "double buffering" if you want more details).
			// I always use vertical synchro.
			bool lVerticalSynchro = true;
			lWindow->swapBuffers();

			// This update some internal counters and listeners.
			// Each render surface (window/rtt/mrt) that is 'auto-updated' has got its 'update' function called.
			lRoot->renderOneFrame();

			// Llamar a esto con handleInput
			// lWindow->destroy();

			Ogre::WindowEventUtilities::messagePump();
		}
		return;
	};

	void OgreApp::createMesh() {
		// A simplistic presentation of some realtime 3D basics.
	// In 3D you need most of the time : 
	// a vertex table Vt + an index table Idt + a kind of primitive P + an associated material M.
	// Let's say P is "triangle" (most common), then Idt will contain
	// a list of index taken from Vt, where each group of 3 index means a triangle.
	// so (Idt[0], Idt[1],Idt[2]) is the first triangle, (Idt[3],Idt[4],Idt[5]) is the second, etc...
	//
	// When times come to render this whole thing, 
	// it will be multiplied by 2 matrix.
	// 1/ a matrix representing transformation(position/orientation/scale) of the thing relative to the camera.
	// 2/ a perspective matrix, corresponding to the parameters of the viewing camera.
	// Ogre will prepare both matrix for you. But you can also provide them if you want.
	// This calculation can be modified in vertex shaders.
	//
	// Once it has been projected, the graphic card uses the buffers (mainly colour and depth)
	// , vertex attributes and material informations (from M) to draw things.
	// vertex attributes are used to 'light', 'colourize', and 'texture' the meshes.
	// This calculation can be partially modified in pixel shaders.
	// This was a very simplistic presentation of 3D rendering ^^.
		{
			// Here, I create a 3D element, by using the interface of ManualObject.
			// ManualObject is very close to the opengl old simple way to specify geometry.
			// There are other interfaces (Hardwarebuffers), you can check the ogremanual fo them and wiki.
			// For each vertex I will provide positions and attributes (normal, vertex color, texture coordinates...).
			// Then for each primitive (given its type : triangle, line, line strip etc...), 
			// I give the corresponding group of vertex index.
			Ogre::ManualObject* lManualObject = NULL;
			{
				// The manualObject creation requires a name.
				Ogre::String lManualObjectName = "CubeWithAxes";
				lManualObject = lScene->createManualObject(lManualObjectName);

				// Always tell if you want to update the 3D (vertex/index) later or not.
				bool lDoIWantToUpdateItLater = false;
				lManualObject->setDynamic(lDoIWantToUpdateItLater);

				// Here I create a cube in a first part with triangles, and then axes (in red/green/blue).

				// BaseWhiteNoLighting is the name of a material that already exist inside Ogre.
				// Ogre::RenderOperation::OT_TRIANGLE_LIST is a kind of primitive.
				float lSize = 0.7f;
				lManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
				{
					float cp = 1.0f * lSize;
					float cm = -1.0f * lSize;

					lManualObject->position(cm, cp, cm);// a vertex
					lManualObject->colour(Ogre::ColourValue(0.0f, 1.0f, 0.0f, 1.0f));
					lManualObject->position(cp, cp, cm);// a vertex
					lManualObject->colour(Ogre::ColourValue(1.0f, 1.0f, 0.0f, 1.0f));
					lManualObject->position(cp, cm, cm);// a vertex
					lManualObject->colour(Ogre::ColourValue(1.0f, 0.0f, 0.0f, 1.0f));
					lManualObject->position(cm, cm, cm);// a vertex
					lManualObject->colour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f));

					lManualObject->position(cm, cp, cp);// a vertex
					lManualObject->colour(Ogre::ColourValue(0.0f, 1.0f, 1.0f, 1.0f));
					lManualObject->position(cp, cp, cp);// a vertex
					lManualObject->colour(Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
					lManualObject->position(cp, cm, cp);// a vertex
					lManualObject->colour(Ogre::ColourValue(1.0f, 0.0f, 1.0f, 1.0f));
					lManualObject->position(cm, cm, cp);// a vertex
					lManualObject->colour(Ogre::ColourValue(0.0f, 0.0f, 1.0f, 1.0f));

					// face behind / front
					lManualObject->triangle(0, 1, 2);
					lManualObject->triangle(2, 3, 0);
					lManualObject->triangle(4, 6, 5);
					lManualObject->triangle(6, 4, 7);

					// face top / down
					lManualObject->triangle(0, 4, 5);
					lManualObject->triangle(5, 1, 0);
					lManualObject->triangle(2, 6, 7);
					lManualObject->triangle(7, 3, 2);

					// face left / right
					lManualObject->triangle(0, 7, 4);
					lManualObject->triangle(7, 0, 3);
					lManualObject->triangle(1, 5, 6);
					lManualObject->triangle(6, 2, 1);
				}
				lManualObject->end();
				// Here I have finished my ManualObject construction.
				// It is possible to add more begin()-end() thing, in order to use 
				// different rendering operation types, or different materials in 1 ManualObject.
				lManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
				{
					float lAxeSize = 2.0f * lSize;
					lManualObject->position(0.0f, 0.0f, 0.0f);
					lManualObject->colour(Ogre::ColourValue::Red);
					lManualObject->position(lAxeSize, 0.0f, 0.0f);
					lManualObject->colour(Ogre::ColourValue::Red);
					lManualObject->position(0.0f, 0.0f, 0.0f);
					lManualObject->colour(Ogre::ColourValue::Green);
					lManualObject->position(0.0, lAxeSize, 0.0);
					lManualObject->colour(Ogre::ColourValue::Green);
					lManualObject->position(0.0f, 0.0f, 0.0f);
					lManualObject->colour(Ogre::ColourValue::Blue);
					lManualObject->position(0.0, 0.0, lAxeSize);
					lManualObject->colour(Ogre::ColourValue::Blue);

					lManualObject->index(0);
					lManualObject->index(1);
					lManualObject->index(2);
					lManualObject->index(3);
					lManualObject->index(4);
					lManualObject->index(5);
				}
				lManualObject->end();
			}
			Ogre::String lNameOfTheMesh = "MeshCubeAndAxe";
			Ogre::String lResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
			lManualObject->convertToMesh(lNameOfTheMesh);

			// Now I can create several entities using that mesh
			int lNumberOfEntities = 5;
			for (int iter = 0; iter < lNumberOfEntities; ++iter)
			{
				Ogre::Entity* lEntity = lScene->createEntity(lNameOfTheMesh);
				// Now I attach it to a scenenode, so that it becomes present in the scene.
				Ogre::SceneNode* lNode = lRootSceneNode->createChildSceneNode();
				lNode->attachObject(lEntity);
				// I move the SceneNode so that it is visible to the camera.
				float lPositionOffset = float(1 + iter * 2) - (float(lNumberOfEntities));
				lNode->translate(lPositionOffset, lPositionOffset, -10.0f);
			}
		}
	}

}