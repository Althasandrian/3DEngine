#include "Include\Resource Manager\ResourceManager.h"
#include <string>
#include "Include\Lodepng\lodepng.h"

int main()
{
	ResourceManager *resman = ResourceManager::GetInstance();

	int res = resman->LoadResource("Resources/Test.vs")->ID;
	Resource* res2 = resman->LoadResource("Resources/bossMusic.wav");
	Resource* res3 = resman->LoadResource("Resources/BigBadBoss.png");
	res2->getAudioData()->audioPlay();
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