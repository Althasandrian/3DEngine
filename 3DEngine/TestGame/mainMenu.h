#ifndef mainMenu_H
#define mainMenu_H

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
#include <Core\Input\Input.h>


class mainMenu : public Engine::Scene
{
public:
	mainMenu();
	virtual ~mainMenu();

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
	Inputs::Input* imput;
};

mainMenu::mainMenu()
{
}

mainMenu::~mainMenu()
{
}

void mainMenu::Init()
{

	EM = Engine::EntityManager::GetInstance();
	SM = Engine::SystemManager::GetInstance();

	SM->AddSystem<Engine::RenderingSystem>(&window, "Resources/Vert.txt", "Resources/Frag.txt");

	if (SM->GetSystem<Engine::RenderingSystem>() != nullptr) {
		SM->GetSystem<Engine::RenderingSystem>()->SetCamera(cam);
	}



}
void mainMenu::Cleanup()
{
	EM->Clear();
	SM->Clear();
}
void mainMenu::Pause()
{

}
void mainMenu::Resume()
{

}
void mainMenu::Update(DeltaTime deltaTime)
{
	EM->Update(deltaTime);
	SM->Update(deltaTime);
	if (imput->getMouseDown(1))
	{
		std::cout << "On to game " << std::endl;
		Engine::SceneManager::GetInstance()->ChangeScene(new TestScene);

	}



}
#endif