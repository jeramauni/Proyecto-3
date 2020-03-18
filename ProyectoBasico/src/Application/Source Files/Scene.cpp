#include "Scene.h"
#include <RenderSystem.h>

Scene::Scene()
{
	_rF = new RenderFactory();
}

Scene::Scene(std::string id) : _id(id)
{
	_rF = new RenderFactory();
}

void Scene::update()
{
	printf("UPDATE");
}

void Scene::render()
{
	/*for (auto i = entidades.begin(); i != entidades.end(); ++i) {
		//new RenderComponent()
		RenderComponent* Rcomp = _rF->Create();
		Rcomp->Init((*i)->_id,
			RenderSystem::getSingleton()->addOgreEntity((*i)->_id));
		(*i)->setNode(Rcomp->getOgreNode());
		(*i)->AddComponent(Rcomp);
	}*/
}

void Scene::push(EntityC * e)
{
	entidades.push_back(e);
}
