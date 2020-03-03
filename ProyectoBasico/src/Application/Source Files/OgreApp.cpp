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
		lOgreInit = new OgreEasy::SimpleOgreInit();
		lOgreInit->initOgre();
	}

	OgreApp::~OgreApp() {
		//OIS::InputManager::destroyInputSystem(mInputMng);
	}

	// I declare a function in which I will make my whole application.
	// This is easy then to add more things later in that function.
	// The main will call this function and take care of the global try/catch.
	void OgreApp::AnOgreApplication() {
		// I construct my object that will allow me to initialise Ogre easily.
	/*	OgreEasy::SimpleOgreInit lOgreInit;

		lOgreInit.initOgre();*/

		/*
		if (!lOgreInit.initOgre()) {
			MWARNING("Impossible to init Ogre correctly.");
			return;
		}
		*/

		// Tener las variables principales a mano
		lRoot = lOgreInit->mRoot.get();
		lWindow = lOgreInit->mWindow;

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

		//----------------------------------INPUT----------------------------------
		okc = new OneKeyComponent();

		// Setup input
		mInputManager = InputManager::getSingletonPtr();
		mInputManager->initialise(lWindow);
		mInputManager->addKeyListener(okc, "Escape");

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

		////--------------------------- LIGHT -----------------------------
		//lightGeneration();

		////-------------------------- MATERIALS -------------------------------
		//materialGeneration(" Mat");

		////--------------------------- ENTIDADES ---------------------------
		//EntityC* _ninja = new EntityC("ninja");
		//RenderComponent* Rcomp = new RenderComponent(_ninja->_id, addEntityToScene(_ninja->_id));
		//_ninja->setNode(Rcomp->getOgreNode());
		//_ninja->AddComponent(Rcomp);

		//--------------------------- MESH -----------------------------
		//squareGeneration();
		//createSquare("MeshCubeAndAxe");
		//meshGeneration();
		//addEntityToScene("ninja", "ninja.mesh");
		//addEntityToScene("Ninja", "penguin.mesh");

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
		
		return;
	};

	void OgreApp::squareGeneration() {
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
		}
	}

	void OgreApp::createSquare(Ogre::String nameOfMesh) {
		// Now I can create several entities using that mesh
		int lNumberOfEntities = 5;
		for (int iter = 0; iter < lNumberOfEntities; ++iter)
		{
			Ogre::Entity* lEntity = lScene->createEntity(nameOfMesh);
			// Now I attach it to a scenenode, so that it becomes present in the scene.
			Ogre::SceneNode* lNode = lRootSceneNode->createChildSceneNode();
			lNode->attachObject(lEntity);
			// I move the SceneNode so that it is visible to the camera.
			float lPositionOffset = float(1 + iter * 2) - (float(lNumberOfEntities));
			lNode->translate(lPositionOffset, lPositionOffset, -10.0f);
		}
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

	void OgreApp::meshGeneration() {
		// Elegir el nombre del grupo
		Ogre::String lNameOfResourceGroup = "Mission 1 : Crear Ninja";
		{
			// Crear el grupo
			Ogre::ResourceGroupManager& lRgMgr = Ogre::ResourceGroupManager::getSingleton();
			lRgMgr.createResourceGroup(lNameOfResourceGroup);

			// Decirle el directorio que se cargara en el grupo
			Ogre::String lDirectoryToLoad = "resources/meshes";
			bool lIsRecursive = false;
			lRgMgr.addResourceLocation(lDirectoryToLoad, "FileSystem", lNameOfResourceGroup, lIsRecursive);

			//Parsea scripts si hay en el grupo
			lRgMgr.initialiseResourceGroup(lNameOfResourceGroup);
			//Cargamos lo que se puede de ese grupo
			lRgMgr.loadResourceGroup(lNameOfResourceGroup);


			//-----------------------------------------------------------------------
			// Creamos entidades que usan esa mesh
			Ogre::String lNameOfTheMesh = "ninja.mesh"; //Addname k sea
			int lNumberOfEntities = 1;
			for (int iter = 0; iter < lNumberOfEntities; ++iter) {
				//Entidad
				Ogre::Entity* lEntity = lScene->createEntity(lNameOfTheMesh);

				//Generamos los materiales
				materialGeneration("Mission 1 : Crear Ninja Mat");
				//Le damos el material a la mesh
				lEntity->setMaterial(lightTextMat(Ogre::MaterialManager::getSingleton(), "Mission 1 : Crear Ninja Mat"));

				//Nodo
				Ogre::SceneNode* lNode = lRootSceneNode->createChildSceneNode();
				lNode->attachObject(lEntity);

				// Mover el nodo para que lo vea la camara
				float lPositionOffset = float(1 + iter * 2) - (float(lNumberOfEntities));
				lPositionOffset = lPositionOffset * 20;
				lNode->translate(lPositionOffset, lPositionOffset, -600.0f);
				lNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));
			}

		}
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
		//lNameOfResourceGroup = "Mission 1 : Crear Ninja Mat";
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

	void OgreApp::SceneCleaner() {
		lScene->destroyAllEntities();
	}

	bool OgreApp::RenderLoop()
	{
		bool f;
		if (!lWindow->isClosed()) {
			// Actualizado de la escena

			// Rotacion de la luz
			Ogre::Degree lAngle(2.5);
			lLightSceneNode->yaw(lAngle);

			//------Input------
			mInputManager->capture();
			if (okc->state) shutDown = true;

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

	// Material sin luz
	Ogre::MaterialPtr OgreApp::noLightMat(Ogre::MaterialManager &matMng, Ogre::String name) {
		// Creacion del material, esto no es perfecto
		Ogre::MaterialPtr lMaterial = matMng.create("M_NoLighting", name);
		//Cambiar a esta
		//Ogre::MaterialManager::getSingleton().create("M_NoLighting", name);

		// Aplicamos la technique y el pass a ese material
		Ogre::Technique* lFirstTechnique = lMaterial->getTechnique(0);
		Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0);

		// Sin luz
		lFirstPass->setLightingEnabled(false);


		//Va a ser blanco, es normal
		return lMaterial;
	}

	// Material con luz
	Ogre::MaterialPtr OgreApp::lightMat(Ogre::MaterialManager& matMng, Ogre::String name) {
		Ogre::MaterialPtr lMaterial = matMng.create("M_LightingColor", name);
		Ogre::Technique* lFirstTechnique = lMaterial->getTechnique(0);
		Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0);
		lFirstPass->setLightingEnabled(true);

		//------------------Caracteristicas de la luz-------------------------
		// Color que "produce" el objeto. Entre 0 y 1
		Ogre::ColourValue lSelfIllumnationColour(0.1f, 0.0f, 0.0f, 1.0f);
		lFirstPass->setSelfIllumination(lSelfIllumnationColour);

		// Color originar del objeto
		Ogre::ColourValue lDiffuseColour(1.0f, 0.4f, 0.4f, 1.0f);
		lFirstPass->setDiffuse(lDiffuseColour);

		// Color ambiental
		Ogre::ColourValue lAmbientColour(0.4f, 0.1f, 0.1f, 1.0f);
		lFirstPass->setAmbient(lAmbientColour);

		// Refleccion de la luz
		Ogre::ColourValue lSpecularColour(1.0f, 1.0f, 1.0f, 1.0f);
		lFirstPass->setSpecular(lSpecularColour);

		/*
		Shininess is the 'inverse of specular color splattering' coefficient.
		If this is big (e.g : 64) you get a very tiny dot with a quite strong color (on round surface).
		If this is 0, you get a simple color layer (the dot has become very wide). 
		*/
		Ogre::Real lShininess = 64.0f;
		lFirstPass->setShininess(lShininess);
		
		return Ogre::MaterialPtr();
	}

	// Material sin luz y con textura
	Ogre::MaterialPtr OgreApp::noLightTextMat(Ogre::MaterialManager& matMng, Ogre::String name)	{
		Ogre::MaterialPtr lMaterial = matMng.create("M_NoLighting+OneTexture", name);
		Ogre::Technique* lFirstTechnique = lMaterial->getTechnique(0);
		Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0);
		lFirstPass->setLightingEnabled(false);

		// Decirle que textura usar
		Ogre::TextureUnitState* lTextureUnit = lFirstPass->createTextureUnitState();
		lTextureUnit->setTextureName("SimpleTexture.bmp", Ogre::TEX_TYPE_2D);
		lTextureUnit->setTextureCoordSet(0);

		return lMaterial;
	}

	// Material con luz y textura
	Ogre::MaterialPtr OgreApp::lightTextMat(Ogre::MaterialManager& matMng, Ogre::String name) {
		Ogre::MaterialPtr lMaterial = matMng.create("M_Lighting+OneTexture", name);
		Ogre::Technique* lFirstTechnique = lMaterial->getTechnique(0);
		Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0);

		// Caracteristicas de la luz
		lFirstPass->setDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
		lFirstPass->setAmbient(0.3f, 0.3f, 0.3f);
		lFirstPass->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
		lFirstPass->setShininess(64.0f);
		lFirstPass->setSelfIllumination(0.1f, 0.1f, 0.1f);

		Ogre::TextureUnitState* lTextureUnit = lFirstPass->createTextureUnitState();
		lTextureUnit->setTextureName("SimpleTexture.bmp", Ogre::TEX_TYPE_2D);
		lTextureUnit->setTextureCoordSet(0);

		return lMaterial;
	}

	// Material con luz, diffuseMap y lightMap
	Ogre::MaterialPtr OgreApp::oneMoreMat(Ogre::MaterialManager& matMng, Ogre::String name)	{
		Ogre::MaterialPtr lMaterial = matMng.create("M_Lighting+DiffuseMap+LightMap", name);
		Ogre::Technique* lFirstTechnique = lMaterial->getTechnique(0);
		Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0);

		lFirstPass->setDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
		lFirstPass->setAmbient(0.3f, 0.3f, 0.3f);
		lFirstPass->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
		lFirstPass->setShininess(64.0f);
		lFirstPass->setSelfIllumination(0.1f, 0.1f, 0.1f);

		Ogre::TextureUnitState* lTextureUnit = lFirstPass->createTextureUnitState();
		lTextureUnit->setTextureName("SimpleTexture.bmp", Ogre::TEX_TYPE_2D);

		// Esta textura usa las coordinadas de la primera textura
		lTextureUnit->setTextureCoordSet(0);

		Ogre::TextureUnitState* lTextureUnit_LM = lFirstPass->createTextureUnitState();
		lTextureUnit_LM->setTextureName("SimpleTexture2.bmp", Ogre::TEX_TYPE_2D);

		lTextureUnit_LM->setTextureCoordSet(1);

		return lMaterial;
	}


}