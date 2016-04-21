#ifndef Scene_h
#define Scene_h

#include <vector>
#include <string>
#include <iostream>
#include "Core/Managers/EntityManager.hpp"

class Scene
{
public:
	Scene(){}
	~Scene(){}

	virtual void update() {};
	virtual void draw() {};
	void load() {};
	void unload() {};

	int id;
	std::string name;

protected:
private:
//	Engine::EntityManager* em = Engine::EntityManager::GetInstance();
	std::vector<Engine::Entity> entities;
	//camera
};

#endif
