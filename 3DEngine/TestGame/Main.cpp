#include "Include\Resource Manager\ResourceManager.h"
#include <string>


int main()
{
	ResourceManager *resman = ResourceManager::GetInstance();

	int res = resman->LoadResource("Resources/Test.txt")->ID;
	//Resource* res2 = resman->LoadResource("Resources/bossMusic.wav");
	Resource* res3 = resman->LoadResource("Resources/test.png");
	Resource* res4 = resman->LoadResource("Resources/test.obj");
	//res2->getAudioData()->audioPlay();
	std::cout << res << std::endl;
	std::cout << res << std::endl;
	std::cout << resman->GetResourceUsers(res) << std::endl;
	resman->UnLoadResource(res);
	std::cout << resman->GetResourceUsers(res) << std::endl;
	std::vector<unsigned char> resvec = res3->getImageData();
	
	resman->UnLoadResource(res);
	std::cout << resman->GetResourceUsers(res) << std::endl;
	system("pause");
	return 0;

}