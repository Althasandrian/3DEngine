// scenes
// transition between scenes
// 
//

//Systeemit ei singletoneja

#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "Scene.h"

class SceneSystem
{
public:
	
	SceneSystem(){}
	~SceneSystem(){}

	Scene* getCurrentScene();
	void changeScenes(int id);
	void addScene(Scene* scene);
	void loadScene(int id);
	void unLoadScene(int id );


protected:

private:
	std::vector<Scene*> sceneList;
	Scene* currentScene;
	void setScene(Scene* scene) {};

};

#endif