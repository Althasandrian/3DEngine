#ifndef Scene_h
#define Scene_h

#include <vector>
#include <string>
#include <iostream>
#include "Core/Managers/EntityManager.hpp"
#include"Core/Time.hpp"
class Scene
{
public:
	Scene(){}
	~Scene(){}

	virtual void update(Engine::DeltaTime dt);
	virtual void draw();
	void load();
	void unload();
	int sceneId;
protected:
private:
//	Engine::EntityManager* em = Engine::EntityManager::GetInstance();
	std::vector<Engine::Entity> entities;

	std::string name;
	
	//camera
};

#endif
