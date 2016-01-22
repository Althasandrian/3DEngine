#include "Resource Manager\ResourceManager.h"
#include "Resource Manager\Resource.h"
#include <string>
int main()
{
	ResourceManager resman;
	std::string res = resman.LoadResource("test.txt")->filepath;
	std::cout << res << std::endl;
	std::cout << resman.GetResourceUsers(res) << std::endl;
	resman.UnLoadResource(res);
	std::cout << resman.GetResourceUsers(res) << std::endl;
	resman.UnLoadResource(res);
	std::cout << resman.GetResourceUsers(res) << std::endl;
	system("pause");
	return 0;
}