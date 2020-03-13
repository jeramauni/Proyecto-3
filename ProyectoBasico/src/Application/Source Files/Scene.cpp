#include "Scene.h"


#include "RenderUtilities.h"
#include "InitOgre.h"






Scene::Scene()
{
	_rF = new RenderFactory();
}

void Scene::update()
{
	printf("UPDATE");
}

void Scene::render(OgreEasy::OgreApp * ogreApp)
{
	for (auto i = entidades.begin(); i != entidades.end(); ++i) {
		//new RenderComponent()
		RenderComponent* Rcomp = _rF->Create();
		Rcomp->Init((*i)->_id, ogreApp->addEntityToScene((*i)->_id));
		(*i)->setNode(Rcomp->getOgreNode());
		(*i)->AddComponent(Rcomp);
	}
}

void Scene::push(EntityC * e)
{
	entidades.push_back(e);
}
