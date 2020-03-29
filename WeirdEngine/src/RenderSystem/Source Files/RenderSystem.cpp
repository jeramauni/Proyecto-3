#include "RenderSystem.h"
#include "WindowRenderer.h"

#include <Ogre.h>
#include <OgrePrerequisites.h>
#include <OgreResourceGroupManager.h>
#include <OgreMeshManager.h>
#include <OgreLogManager.h>
#include <OgreLog.h>
#include <OgreBuildSettings.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreCompositorManager.h>

RenderSystem* RenderSystem::instance_ = nullptr;

bool RenderSystem::initSingleton()
{
	if (instance_ == nullptr) {
		instance_ = new RenderSystem();

		return true;
	}
	return false;
}

RenderSystem* RenderSystem::getSingleton()
{
	return instance_;
}

RenderSystem::RenderSystem() {
	WindowRenderer::initSingleton();
	//mScnMgr = WindowRenderer::getSingleton()->getRoot()->createSceneManager();
}

RenderSystem::~RenderSystem() {

}

Ogre::SceneNode* RenderSystem::addOgreEntity(Ogre::String name)
{
	Ogre::Entity* mEntity = mScnMgr->createEntity(name, name + ".mesh");
	Ogre::SceneNode* mNode = addEmpty(name);
	
	mEntity->setMaterialName(name);

	mNode->attachObject(mEntity);

	// Mover el nodo para que lo vea la camara
	float lPositionOffset = float(1 * 2) - (float(1));
	lPositionOffset = lPositionOffset * 20;
	mNode->translate(lPositionOffset, lPositionOffset, -600.0f);
	mNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));

	return mNode;
}

Ogre::SceneNode* RenderSystem::addEmpty(Ogre::String name)
{
	return mScnMgr->getRootSceneNode()->createChildSceneNode(name);
}

Ogre::Entity* RenderSystem::getEntityByName(Ogre::String name)
{
	return mScnMgr->getEntity(name);
}

inline Ogre::SceneNode* RenderSystem::getRootNode()
{
	return mScnMgr->getRootSceneNode();
}

inline void RenderSystem::setSceneManager(Ogre::SceneManager* sm)
{
	mScnMgr = sm;
}

Ogre::SceneNode* RenderSystem::createLight(Ogre::String name, LightTypes type, Ogre::ColourValue diffuse, Ogre::ColourValue specular)
{
	Ogre::Light* light = mScnMgr->createLight(name);
	light->setType(Ogre::Light::LightTypes(type));
	light->setDiffuseColour(diffuse);
	light->setSpecularColour(specular);

	Ogre::SceneNode* mLightNode = mScnMgr->getRootSceneNode()->createChildSceneNode(name);
	mLightNode->attachObject(light);

	return mLightNode;
}

void RenderSystem::setAmbientLight(Ogre::ColourValue color)
{
	mScnMgr->setAmbientLight(color);
}

void RenderSystem::setMaterial(Ogre::String entity, Ogre::String matName)
{
	getEntityByName(entity)->setMaterialName(matName);
}

void RenderSystem::setMaterial(Ogre::Entity* ent, Ogre::String matName)
{
	ent->setMaterialName(matName);
}

void RenderSystem::materialGeneration(Ogre::String nameOfResourceGroup)
{
	Ogre::MaterialManager& materialManager = Ogre::MaterialManager::getSingleton();

	Ogre::ResourceGroupManager& mRgMgr = Ogre::ResourceGroupManager::getSingleton();
	mRgMgr.createResourceGroup(nameOfResourceGroup);

	// Textures directory path
	Ogre::String textureDirectory = "resources/textures";
	mRgMgr.addResourceLocation(textureDirectory, "FileSystem", nameOfResourceGroup);

	// Initialise all resources
	mRgMgr.initialiseAllResourceGroups();

	// Load the desired resource group
	mRgMgr.loadResourceGroup(nameOfResourceGroup);
}

Ogre::Camera* RenderSystem::getCamera()
{
	return camera;
}

Ogre::SceneNode* RenderSystem::getCameraNode()
{
	return camera->getParentSceneNode();
}

Ogre::Viewport* RenderSystem::getViewport()
{
	return camera->getViewport();
}

void RenderSystem::setSkyBox(Ogre::String matName, Ogre::Real distance)
{
	mScnMgr->setSkyBox(true, matName, distance);
}

void RenderSystem::addCamera(int zOrder)
{

	float viewportWidth = 0.88f;
	float viewportHeight = 0.88f;
	float viewportLeft = (1.0f - viewportWidth) * 0.5f;
	float viewportTop = (1.0f - viewportHeight) * 0.5f;
	//unsigned short mainViewportZOrder = 100;


	Ogre::Camera* mCamera = nullptr;
	mCamera = mScnMgr->createCamera("MainCam");

	Ogre::SceneNode* mCamNode = nullptr;
	mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(mCamera);

	mCamNode->setPosition(0, 0, 1);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = WindowRenderer::getSingleton()->getWin()->addViewport(mScnMgr->getCamera("MainCam"),
		zOrder, viewportLeft, viewportTop, viewportWidth, viewportHeight);
	camera = mScnMgr->getCamera("MainCam");


	vp->setAutoUpdated(true);

	// Color for the viewPort
	vp->setBackgroundColour(Ogre::ColourValue(1, 0, 1));

	// I choose the visual ratio of the camera. To make it looks real, I want it the same as the viewport. 
	float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
	mCamera->setAutoAspectRatio(true);



	//If (far/near)>2000 then you will likely get 'z fighting' issues.
	mCamera->setNearClipDistance(3.0f);
	mCamera->setFarClipDistance(4000.0f);

}

void RenderSystem::createScene(Ogre::String sceneName)
{
	Ogre::SceneManager* s = WindowRenderer::getSingleton()->getRoot()->createSceneManager();
	mScnMgr = s;
	scenes.erase(sceneName);
	scenes.insert({ sceneName, mScnMgr });
	
	int zOrder;

	if (sceneName == "gameplay") zOrder = 100;
	else zOrder = 50;

	addCamera(zOrder);

	setAmbientLight(Ogre::ColourValue(0.2f, 0.0f, 0.2f, 1.0f));

}

void RenderSystem::setRenderingScene(Ogre::String sceneName)
{

	WindowRenderer::getSingleton()->getWin()->removeAllViewports();

	Ogre::SceneManager* sm = scenes.find(sceneName)->second;


	float viewportWidth = 0.88f;
	float viewportHeight = 0.88f;
	float viewportLeft = (1.0f - viewportWidth) * 0.5f;
	float viewportTop = (1.0f - viewportHeight) * 0.5f;
	unsigned short mainViewportZOrder = 100;

	Ogre::Viewport* vp = WindowRenderer::getSingleton()->getWin()->addViewport(sm->getCamera("MainCam"),
			mainViewportZOrder, viewportLeft, viewportTop, viewportWidth, viewportHeight);

	sm->getCamera("MainCam")->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight())); //in case this has changed

	mScnMgr = sm;
	camera = mScnMgr->getCamera("MainCam");

	currentScene = sceneName;
}

void RenderSystem::clearScene()
{
	mScnMgr->destroyAllEntities();
}

Ogre::String RenderSystem::getCurrentScene()
{
	return currentScene;
}


void RenderSystem::squareGeneration() {
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
			lManualObject = mScnMgr->createManualObject(lManualObjectName);

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