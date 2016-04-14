#include "Scene.h"

void Scene::update(Engine::DeltaTime dt) 
{
	for (auto it : entities)
	{
		it.Update(dt);
	}
}
void Scene::draw() 
{
	//virtual??
}
void Scene::load() 
{
	//load entities
	//load textures
	//load audio
	//load other possible stuff
}
void Scene::unload() 
{
	//unload above mentioned stuff
}