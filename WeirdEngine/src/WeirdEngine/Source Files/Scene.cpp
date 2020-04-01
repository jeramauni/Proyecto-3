#include "Scene.h"

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