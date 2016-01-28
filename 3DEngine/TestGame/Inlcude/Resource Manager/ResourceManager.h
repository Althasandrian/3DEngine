#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <vector>
#include "Resource Manager\Resource.h"


class ResourceManager
{
public:
	ResourceManager()
	{

	}
	~ResourceManager() {}
	static ResourceManager* GetInstance();
	Resource* LoadResource(std::string filepath);
	void UnLoadResource(int ID);
	int GetResourceUsers(int ID);
private:
	std::vector<Resource*> _resources;
	std::vector<Resource*>::iterator _it;
	int ID_generator = 0;
	static ResourceManager* Instance;

};

#endif