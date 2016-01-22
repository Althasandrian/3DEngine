#include "Resource Manager\ResourceManager.h"
#include "Resource Manager\Resource.h"
#include <string>
int main()
{
	ResourceManager resman;
	resman.LoadResource("test.txt");
	std::string res = resman.LoadResource("test.txt")->UID;
	std::cout << res << std::endl;
	std::cout << resman.GetResourceUsers("name") << std::endl;
	resman.UnLoadResource(res);
	std::cout << resman.GetResourceUsers("name2") << std::endl;
	resman.UnLoadResource(res);
	std::cout << resman.GetResourceUsers("name") << std::endl;
	system("pause");
	return 0;
}