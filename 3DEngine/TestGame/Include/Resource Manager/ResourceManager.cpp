#include "ResourceManager.h"
#include <string>
#include <fstream>
#include <Windows.h>
ResourceManager* ResourceManager::Instance = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (Instance == nullptr)
	{
		std::cout << "Creating a new resource manager. " << std::endl;
		Instance = new ResourceManager;

	}
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
	//TextFile
	if (filepath.substr(filepath.size() - 4) == ".txt")
	{
		std::cout << "A text file" << std::endl;
		Resource* res = new Resource(); 
		res = ResourceManager::LoadTextResource(filepath);
		return res;
	}
	//ImageFile
	else if (filepath.substr(filepath.size() - 4) == ".png")
	{
		std::cout << "An image file" << std::endl;

		Resource * res = new Resource();
		res = ResourceManager::LoadImageResource(filepath);
		return res;
	}
	//AudioFile
	else if (filepath.substr(filepath.size() - 4) == ".wav")
	{
		std::cout << "An audio file" << std::endl;

		Resource *res = new Resource();
		res = ResourceManager::LoadAudioResource(filepath);

		return res;
	}
	//FontFile
	else if (filepath.substr(filepath.size() - 4) == ".ttf")
	{
		std::cout << "a Font file" << std::endl;

		
			unsigned size = strlen(filepath.c_str()) + 1; // +1 to include NULL
			wchar_t* wc = new wchar_t[size];
			unsigned outSize;
			mbstowcs_s(&outSize, wc, size, filepath.c_str(), size - 1);
			
		

		AddFontResourceEx(wc , FR_PRIVATE,0);
		
		Resource *res = new Resource();
		res = ResourceManager::LoadFontResource(filepath);
		return res;
	}
	//UnknownFile
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

Resource* ResourceManager::LoadTextResource(std::string filepath)
{
	std::cout << "Loading Resource" << std::endl;
	Resource * res = new Resource;
	res->filepath = filepath;
	res->type = Text;
	res->ID = ++ID_generator;
	res->resourceUsers.push_back(1);

	std::ifstream file(filepath, std::ifstream::binary);
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
		res->setTextData(readFile);//

	}
	_resources.push_back(res);
	return res;
}
Resource* ResourceManager::LoadImageResource(std::string filepath)
{

	std::cout << "Loading resource" << std::endl;
	unsigned width, height;

	Resource * res = new Resource();
	res->filepath = filepath;
	res->type = Image;
	res->ID = ++ID_generator;
	res->resourceUsers.push_back(1);
	
	std::ifstream file(filepath, std::ifstream::binary);
	if (file.is_open())
	{
		// Get size of file///////////
		file.seekg(0, file.end);	//
		int size = file.tellg();	//
		file.seekg(0, file.beg);	//

		// Allocate buffer//////////////
		char* buffer = new char[size];//

		// Read file//////////////////
		file.read(buffer, size);	// 
		buffer[size] = NULL;		//
		file.close();				//

		std::vector<unsigned char> imgfile;
		unsigned error = lodepng::decode(imgfile,width,height,filepath);

		res->setImageData(imgfile);

	}
	_resources.push_back(res);
	return res;
}
Resource* ResourceManager::LoadAudioResource(std::string filepath)
{
	std::cout << "Loading Resource" << std::endl;

	Resource *res = new Resource();
	res->filepath = filepath;
	res->type = Audio;
	res->ID = ++ID_generator;
	res->resourceUsers.push_back(1);
	
	irrklang::ISoundSource* audioFile = soundEngine->addSoundSourceFromFile(filepath.c_str());

	res->setAudioData(/*audioFile*/);
	_resources.push_back(res);
	return res;
}
Resource* ResourceManager::LoadFontResource(std::string filepath)
{
	std::cout << "Loading Resource" << std::endl;

	Resource *res = new Resource();
	res->filepath = filepath;
	res->type = Font;
	res->ID = ++ID_generator;
	res->resourceUsers.push_back(1);

	_resources.push_back(res);
	return res;
}