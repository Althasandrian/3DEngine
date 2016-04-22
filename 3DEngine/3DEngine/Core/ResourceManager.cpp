#include "ResourceManager.h"
#include <string>
#include <fstream>
#include <Windows.h>
#include "..\Lodepng\lodepng.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <..\Dependencies\include\tiny_obj_loader\tiny_obj_loader.h>

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
	for (auto i : _resources)
	{
		if (i->filepath == filepath)
		{
			std::cout << "resource already loaded" << std::endl;
			i->resourceUsers.push_back(1);
			return i;
		}
	}

	//TextFile
	if (filepath.substr(filepath.size() - 4) == ".txt" || filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
	{ 
		if (filepath.substr(filepath.size() - 3) == ".vs" || filepath.substr(filepath.size() - 3) == ".fs")
		{
			std::cout << "Loading shader file" << std::endl;
			// load shader file
		}
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
		std::cout << "a font file" << std::endl;

		
			unsigned size = strlen(filepath.c_str()) + 1; // +1 to include NULL
			wchar_t* wc = new wchar_t[size];
			unsigned outSize;
			mbstowcs_s(&outSize, wc, size, filepath.c_str(), size - 1);

		AddFontResourceEx(wc , FR_PRIVATE,0);
		
		Resource *res = new Resource();
		res = ResourceManager::LoadFontResource(filepath);
		return res;
	}
	else if (filepath.substr(filepath.size() - 4) == ".obj")
	{
		std::cout << "An object file" << std::endl;

		Resource *res = new Resource();
		res = ResourceManager::LoadObjectResource(filepath);

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
	
	std::vector<unsigned char> image;
	unsigned error = lodepng::decode(image,width,height,filepath);

	res->setImageData(image, width, height);

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
	
	
	res->setAudioEngine(soundEngine);
	
	res->setAudio(filepath);
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
Resource* ResourceManager::LoadObjectResource(std::string filepath)
{

	std::cout << "Loading Resource" << std::endl;

	Resource *res = new Resource();
	res->filepath = filepath;
	res->type = OBJ;
	res->ID = ++ID_generator;
	res->resourceUsers.push_back(1);

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	tinyobj::LoadObj(shapes, materials, err, filepath.c_str(), "Resources/");

	if (!err.empty()) {
		std::cout << err << std::endl;
	}


	for (size_t i = 0; i < shapes.size(); i++) {
		size_t offset = res->_vertices.size();
		for (size_t j = 0; j < shapes[i].mesh.positions.size() / 3; j++)
		{
			res->_vertices.push_back(glm::vec3(shapes[i].mesh.positions[3 * j + 0], shapes[i].mesh.positions[3 * j + 1], shapes[i].mesh.positions[3 * j + 2]));
		}
		for (size_t j = 0; j < shapes[i].mesh.indices.size() / 3; j++) {
			res->_indices.push_back(glm::uvec3(shapes[i].mesh.indices[3 * j + 0] + offset, shapes[i].mesh.indices[3 * j + 1] + offset, shapes[i].mesh.indices[3 * j + 2] + offset));
		}
	}

	_resources.push_back(res);
	return res;
}
