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

Ogre::SceneNode* RenderSystem::addOgreEntity(std::string name)
{
	Ogre::Entity* mEntity = mScnMgr->createEntity(name, name + ".mesh");
	Ogre::SceneNode* mNode = addEmpty(name);
	
	mEntity->setMaterialName(name);

	mNode->attachObject(mEntity);

	// Mover el nodo para que lo vea la camara
	//float lPositionOffset = float(1 * 2) - (float(1));
	//lPositionOffset = lPositionOffset * 20;
	//mNode->translate(lPositionOffset, lPositionOffset, -600.0f);
	//mNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));

	return mNode;
}

Ogre::SceneNode* RenderSystem::addEmpty(std::string name)
{
	return mScnMgr->getRootSceneNode()->createChildSceneNode(name);
}

Ogre::Entity* RenderSystem::getEntityByName(std::string name)
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

Ogre::SceneNode* RenderSystem::createLight(std::string name, LightTypes type, Ogre::ColourValue diffuse, Ogre::ColourValue specular)
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

void RenderSystem::setMaterial(std::string entity, std::string matName)
{
	getEntityByName(entity)->setMaterialName(matName);
}

void RenderSystem::setMaterial(Ogre::Entity* ent, std::string matName)
{
	ent->setMaterialName(matName);
}

void RenderSystem::materialGeneration(std::string nameOfResourceGroup)
{
	Ogre::MaterialManager& materialManager = Ogre::MaterialManager::getSingleton();

	Ogre::ResourceGroupManager& mRgMgr = Ogre::ResourceGroupManager::getSingleton();
	mRgMgr.createResourceGroup(nameOfResourceGroup);

	// Textures directory path
	std::string textureDirectory = "resources/textures";
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

void RenderSystem::setSkyBox(std::string matName, Ogre::Real distance)
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

void RenderSystem::createScene(std::string sceneName)
{
	Ogre::SceneManager* s = WindowRenderer::getSingleton()->getRoot()->createSceneManager();
	mScnMgr = s;
	scenes.erase(sceneName);
	scenes.insert({ sceneName, mScnMgr });
	
	int zOrder;

	if (sceneName == "gameplay") zOrder = 100;
	else zOrder = 50;

	addCamera(zOrder);

	//--------------------------- LIGHT -----------------------------
	//Creacion de la luz en la escena
	setAmbientLight(Ogre::ColourValue(0.2f, 0.0f, 0.2f, 1.0f));
}

void RenderSystem::setRenderingScene(std::string sceneName) {
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

std::string RenderSystem::getCurrentScene()
{
	return currentScene;
}