#include "Resource Manager\ResourceManager.h"
#include <string>

int main()
{
	ResourceManager *resman = ResourceManager::GetInstance();

	int res = resman->LoadResource("Resources/Test.txt")->ID;
	int res2 = resman->LoadResource("Resources/img.img")->ID;
	std::cout << res << std::endl;
	std::cout << res2 << std::endl;
	std::cout << resman->GetResourceUsers(res) << std::endl;
	resman->UnLoadResource(res);
	std::cout << resman->GetResourceUsers(res) << std::endl;
	resman->UnLoadResource(res2);
	std::cout << resman->GetResourceUsers(res) << std::endl;
	system("pause");
	return 0;
}