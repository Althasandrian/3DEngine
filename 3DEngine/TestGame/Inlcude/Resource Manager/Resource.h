#ifndef RESOURCE_H
#define RESOURCE_H
#include <iostream>

enum TYPE
{
	Text = 1,
	Audio = 2,
	Image = 3,
	Video = 4,
};
class Resource
{
public:
	Resource() {};
	~Resource(){};

	std::string filepath;
	TYPE type;
	std::string scope; 
	int ID;
	std::vector<int> resourceUsers;
	void setTextData(std::string readFile){ textData = readFile; }
	void setImageData(std::vector<char> imageFile) { std::cout << "setting image data" << std::endl; imageData = imageFile; }
	std::string getTextData(){ return textData; }
	std::vector<char> getImageData(){ return imageData; }
private:
	std::string textData;
	std::vector<char> imageData;
	
};

#endif