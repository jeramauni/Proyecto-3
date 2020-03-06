#include "Scene.h"

#include "RenderComponent.h"
#include "RenderUtilities.h"
#include "InitOgre.h"

void Scene::update()
{
	printf("UPDATE");
}

void Scene::render(OgreEasy::OgreApp * ogreApp)
{
	for (auto i = entidades.begin(); i != entidades.end(); ++i) {
		RenderComponent* Rcomp = new RenderComponent((*i)->_id, ogreApp->addEntityToScene((*i)->_id));
		(*i)->setNode(Rcomp->getOgreNode());
		(*i)->AddComponent(Rcomp);
	}
}

void Scene::push(EntityC * e)
{
	entidades.push_back(e);
}
