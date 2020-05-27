#include "AddCameraToSceneComponent.h"
#include "ComponentFactory.h"

#include "messages_defs.h"
#include "Utilities\Vector4.h"

#include <Ogre.h>

//CREATE_REGISTER(AddCameraToScene);

AddCameraToSceneComponent::AddCameraToSceneComponent(Container* e) {
	_name = "AddCameraToScene";
	_parent = e;

	e->getWEManager()->addCameraToScene(Vector4{ 0.2, 0.0, 0.2, 0.8 });
}

AddCameraToSceneComponent::~AddCameraToSceneComponent() {

}

void AddCameraToSceneComponent::Init(std::unordered_map<std::string, std::string>& param) {

}

void AddCameraToSceneComponent::update(Container* c, float time) {

}

void AddCameraToSceneComponent::receive(Container* c, const msg::Message& msg) {

}
