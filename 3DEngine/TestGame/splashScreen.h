#ifndef splashscreen_h
#define splashscreen_h

#include <Core\Managers\EntityManager.hpp>
#include <Core\Managers\SystemManager.hpp>
#include <Core\Managers\SceneManager.hpp>
#include <Core/ResourceManager.h>

#include <Core/Systems/RenderingSystem.hpp>

#include <Core/Components/Render.hpp>
#include <Core/Components/Color.hpp>
#include <Core/Components/Audio.h>

#include <Core\Time.hpp>
#include <Core\Window.h>
#include <Core\Camera.hpp>
#include "mainMenu.h"


class splashScreen : public Engine::Scene
{
public:
	splashScreen();
	virtual ~splashScreen();

	virtual void Init(); //= 0;												//		//
	virtual void Cleanup();// = 0;												//		//
	//		//
	virtual void Pause(); //= 0;												//		//
	virtual void Resume(); //= 0;												//		//
	//		//
	virtual void Update(DeltaTime deltaTime);// = 0;

private:
	Engine::EntityManager* EM;
	Engine::SystemManager* SM;
	Camera* cam;
	Window window;
	DeltaTime Duration = 3;
};

splashScreen::splashScreen()
{
}

splashScreen::~splashScreen()
{
}

void splashScreen::Init()
{

	EM = Engine::EntityManager::GetInstance();
	SM = Engine::SystemManager::GetInstance();

	SM->AddSystem<Engine::RenderingSystem>(&window,"Resources/Vert.txt","Resources/Frag.txt");

	if (SM->GetSystem<Engine::RenderingSystem>() != nullptr) {
		SM->GetSystem<Engine::RenderingSystem>()->SetCamera(cam);
	}



}
void splashScreen::Cleanup()
{
	EM->Clear();
	SM->Clear();
}
void splashScreen::Pause()
{

}
void splashScreen::Resume()
{

}
void splashScreen::Update(DeltaTime deltaTime)
{
	EM->Update(deltaTime);
	SM->Update(deltaTime);
	if ((Duration -= deltaTime ) < 0 )
	{
		std::cout << deltaTime << " " << Duration << std::endl;
	Engine::SceneManager::GetInstance()->ChangeScene(new mainMenu);
	std::cout << "Changing scene" << std::endl;
	}
	
	

}
#endif