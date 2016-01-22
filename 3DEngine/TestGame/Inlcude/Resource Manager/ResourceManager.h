#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <vector>
#include "Resource Manager\Resource.h"


class ResourceManager
{
public:
	ResourceManager() {}
	~ResourceManager() {}

	Resource* LoadResource(std::string filepath);
	void UnLoadResource(std::string filepath);
	int GetResourceUsers(std::string filepath);
private:
	std::vector<Resource*> _resources;
	std::vector<Resource*>::iterator _it;
	//int _resourceUsers;

};

#endif