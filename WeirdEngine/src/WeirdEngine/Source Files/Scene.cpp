#include "Scene.h"
#include "Messages_defs.h"

#include <EntityC.h>

Scene::Scene() {

}

Scene::Scene(std::string id) :_id(id) {

}

void Scene::update() {
	for (auto i = entidades.begin(); i != entidades.end(); ++i) {
		static_cast<EntityC*>(*i)->update();
	}
}

void Scene::addEntity(EntityC * e) {
	entidades.push_back(e);
}

void Scene::send(const void* senderObj, const msg::Message& msg) {
	for (EntityC* e : listeners) {
		if (senderObj != e) {
			if (msg.destination_ == msg::Broadcast || msg.destination_ == e->getId())
			e->receive(senderObj, msg);
		}
	}
}