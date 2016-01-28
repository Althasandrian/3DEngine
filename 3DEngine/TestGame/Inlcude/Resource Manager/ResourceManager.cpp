#include "Resource Manager\ResourceManager.h"
#include <string>
#include <fstream>
ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (Instance == nullptr)
		Instance = new ResourceManager;
	return Instance;
}
Resource* ResourceManager::LoadResource(std::string filepath)
{

	for ( _it = _resources.begin(); _it != _resources.end(); _it++)
	{
		{
			if ((*_it)->filepath== filepath)

			{
				std::cout << "resource already loaded" << std::endl;
				(*_it)->resourceUsers.push_back(1);
				return *_it;
			}
		}
	}
	if (filepath.substr(filepath.size() - 4) == ".txt")
	{
		std::cout << "A text file" << std::endl;
		std::cout << "Loading Resource" << std::endl;
		Resource *res = new Resource();
		res->filepath = filepath;
		res->type = Text;
		res->ID = ++ID_generator;
		res->resourceUsers.push_back(1);
		_resources.push_back(res);

		std::ifstream file(filepath,std::ifstream::binary);
		if (file.is_open())
		{			
			// Get size of file///////////
			file.seekg(0, file.end);	//
			int size = file.tellg();	//
			file.seekg(0, file.beg);	//

			// Allocate buffer for text/////
			char* buffer = new char[size];//


			// Read file//////////////////
			file.read(buffer, size);	//
			buffer[size] = NULL;		//
			file.close();				//

			//Change text into string/////
			std::string readFile;		//
			readFile = buffer;			//

			//Set text to resource////////
			res->setTextData( readFile);//

		}
		return res;
	}
	else if (filepath.substr(filepath.size() - 4) == ".img")
	{
		std::cout << "An image file" << std::endl;
		std::cout << "Loading resource" << std::endl;
		Resource * res = new Resource();
		res->filepath = filepath;
		res->type = Image;
		res->ID = ++ID_generator;
		res->resourceUsers.push_back(1);
		_resources.push_back(res);
		return res;
	}
	else if (filepath.substr(filepath.size() - 4) == ".aud")
	{
		std::cout << "An audio file" << std::endl;
		std::cout << "Loading Resource" << std::endl;
		Resource *res = new Resource();
		res->filepath = filepath;
		res->type = Audio;
		res->ID = ++ID_generator;
		res->resourceUsers.push_back(1);
		_resources.push_back(res);
		return res;
	}
	else if (filepath.substr(filepath.size() - 4) == ".vid")
	{
		std::cout << "a video file" << std::endl;
		std::cout << "Loading Resource" << std::endl;
		Resource *res = new Resource();
		res->filepath = filepath;
		res->type = Video;
		res->ID = ++ID_generator;
		res->resourceUsers.push_back(1);
		_resources.push_back(res);
		return res;
	}
	else
	{
		std::cout << "filetype not regognized" << std::endl;
		return 0;
	}

}
void ResourceManager::UnLoadResource(int ID)
{
	
	_it = _resources.begin();
	while (_it != _resources.end())
	{
		if ((*_it)->ID== ID)
		{
			std::cout << "Deleting resource" << std::endl;
			(*_it)->resourceUsers.pop_back();
			if ((*_it)->resourceUsers.size() <= 0)
			{
				std::cout << "unloading resource" << std::endl;
				_it = _resources.erase(_it);
			}
			else
				_it++;
		}
		else
			_it++;
	}

}
int ResourceManager::GetResourceUsers(int ID)
{
	_it = _resources.begin();
	while (_it != _resources.end())
	{
		if ((*_it)->ID == ID)
		{
			return (*_it)->resourceUsers.size();
		}
		_it++;
	}
	std::cout << "Resource not found" << std::endl;
	return 0;
}