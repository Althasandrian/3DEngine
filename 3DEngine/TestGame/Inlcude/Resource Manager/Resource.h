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


	std::string UID;
	std::string filepath;
	TYPE type;
	std::string scope; 
	std::vector<int> resourceUsers;
private:

};

#endif