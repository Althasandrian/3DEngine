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
	std::string getTextData(){ return textData; }
private:
	std::string textData;
	
};

#endif