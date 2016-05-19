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
	DeltaTime Duration = 3;
	std::shared_ptr<Engine::Entity> test;
};

splashScreen::splashScreen() 
{
}

splashScreen::~splashScreen() 
{
}

void splashScreen::Init()  
{
	cam = new Camera();

	EM = Engine::EntityManager::GetInstance();
	SM = Engine::SystemManager::GetInstance();

	SM->AddSystem<Engine::PhysicsSystem>();
	SM->AddSystem<Engine::RenderingSystem>(&window, "Resources/Vert.txt", "Resources/Frag.txt");

	if (SM->GetSystem<Engine::RenderingSystem>() != nullptr) {
		SM->GetSystem<Engine::RenderingSystem>()->SetCamera(cam);
	}

	Resource* box = ResourceManager::GetInstance()->LoadResource("Resources/cube.obj");

	test = EM->AddEntity("box", std::make_shared<player>());

	EM->AddComponent<Engine::Render>("box", box->_vertices, box->_indices);
	EM->AddComponent<Engine::Transform>("box", glm::vec3(0.0f, 0.0f, -17.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	EM->AddComponent<Engine::AABB>("box");
	EM->AddComponent<Engine::Texture>("box", "Resources/Texture4.png");


	//EM->AddEntity("asd", std::make_shared<Engine::Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), -1.0f));
	//EM->AddComponent<Engine::Texture>("asd", "Resources/Texture4.png");


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