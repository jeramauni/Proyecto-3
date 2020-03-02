#include "Scene.h"

#include "RenderComponent.h"
#include "RenderUtilities.h"
#include "InitOgre.h"

void Scene::update()
{
	//for (auto i = entidades.begin(); i != entidades.end(); ++i) { (*i)->update(); }
}

void Scene::render(OgreEasy::OgreApp * ogreApp)
{
	//EntityC* _ninja = new EntityC("ninja");
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
