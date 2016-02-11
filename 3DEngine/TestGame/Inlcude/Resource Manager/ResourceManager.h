#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <vector>
#include "Resource Manager\Resource.h"


class ResourceManager
{
public:

	static ResourceManager* GetInstance();
	Resource* LoadResource(std::string filepath);
	Resource* LoadTextResource(std::string filepath);
	Resource* LoadImageResource(std::string filepath);
	Resource* LoadAudioResource(std::string filepath);
	Resource* LoadVideoResource(std::string filepath);
	void UnLoadResource(int ID);
	int GetResourceUsers(int ID);

private:

	ResourceManager(){}
	~ResourceManager() {}
	std::vector<Resource*> _resources;
	std::vector<Resource*>::iterator _it;
	int ID_generator = 0;
	static ResourceManager* Instance;


};

#endif