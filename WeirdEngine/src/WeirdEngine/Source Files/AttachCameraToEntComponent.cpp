#include "AttachCameraToEntComponent.h"

#include "messages_defs.h"
#include "Utilities\Vector4.h"

#include <Ogre.h>
#include "ComponentFactory.h"

CREATE_REGISTER(AttachCameraToEnt);

AttachCameraToEntComponent::AttachCameraToEntComponent(Container* e) {
	_name = "AttachCameraToEnt";
	_parent = e;
	Ogre::Camera* mCam = e->getWEManager()->getCam();

	e->getWEManager()->addCameraToEntity(e->GetEntityName(), Vector4{ 0.2, 0.0, 0.2, 0.8 });
}

AttachCameraToEntComponent::~AttachCameraToEntComponent() {

}

void AttachCameraToEntComponent::Init(std::unordered_map<std::string, std::string>& param) {

}

void AttachCameraToEntComponent::update(Container* c, float time) {

}

void AttachCameraToEntComponent::receive(Container* c, const msg::Message& msg) {

}
