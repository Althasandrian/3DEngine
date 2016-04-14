#include "Scene.h"

void Scene::update(Engine::DeltaTime dt) 
{
	for (auto i = 0; i < entities.size(); i++)
	{
		entities.at(i).Update(dt);
	}
}
void Scene::draw() 
{
	
}
void Scene::load() 
{

}
void Scene::unload() 
{

}