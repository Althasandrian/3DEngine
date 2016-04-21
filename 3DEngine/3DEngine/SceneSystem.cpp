#include "SceneSystem.h"

Scene* SceneSystem::getCurrentScene()
{
	return currentScene;
}
void SceneSystem::changeScenes(int id)
{
	for (int i = 0; i < sceneList.size();i++)
	{
		if (sceneList.at(i)->id == id)
		{
			setScene(sceneList.at(i));
			return;
		}
	}
	std::cout << "scene not found" << std::endl;

}
void SceneSystem::addScene(Scene* scene)
{
	sceneList.push_back(scene);
}
void SceneSystem::loadScene(int id)
{
	for (int i = 0; i < sceneList.size(); i++)
	{
		if (sceneList.at(i)->id == id)
		{
			sceneList.at(i)->load();
			return;
		}
	}
	std::cout << "scene not found" << std::endl;
}
void SceneSystem::unLoadScene(int id)
{
	for (int i = 0; i < sceneList.size(); i++)
	{
		if (sceneList.at(i)->id == id)
		{
			sceneList.at(i)->unload();
			return;
		}
	}
	std::cout << "scene not found" << std::endl;
}