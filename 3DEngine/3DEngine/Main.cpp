#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "Core/Window.h"
#include "Core/Time.hpp"
#include <glew.h>
#include <windows.h>
#include <Core/Input/Input.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <lib/Helper.hpp>

#include <Core/Managers/EntityManager.hpp>
#include <Core/Managers/SystemManager.hpp>
#include <Core/Systems/RenderingSystem.hpp>
#include <Core/Systems/PhysicsSystem.hpp>

#include <Core/Components/Renderable.hpp>
#include <Core/Components/Color.hpp>
#include <Core/Components/AABB.hpp>

#include <Core/Managers/SceneManager.hpp>

#include <Core/ResourceManager.h>

#include <Core/Camera.hpp>
#include <Scene.h>

class player : public Engine::Entity
{
public:
	player(){};
	virtual ~player(){};

	void Init(){};
	void Cleanup(){};
	void Update(DeltaTime dt){};

	
};

Window window;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		window.Resize();
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

class TestScene : public Engine::Scene
{
public:
	TestScene() {};
	virtual ~TestScene() {};

	virtual void Init()  override {
		cam = new Camera();

		EM = Engine::EntityManager::GetInstance();
		SM = Engine::SystemManager::GetInstance();

		SM->AddSystem<Engine::PhysicsSystem>();
		SM->AddSystem<Engine::RenderingSystem, Window*>(&window);

		if (SM->GetSystem<Engine::RenderingSystem>() != nullptr) {
			SM->GetSystem<Engine::RenderingSystem>()->SetCamera(cam);
		}

		player1 = EM->AddEntity("player", std::make_shared<player>());
		test = EM->AddEntity("box", std::make_shared<player>());


		Resource* monkey = ResourceManager::GetInstance()->LoadResource("Resources/Monkey.obj");
		Resource* box = ResourceManager::GetInstance()->LoadResource("Resources/Box.obj");

		EM->AddComponent<Engine::Renderable>("player", monkey->_vertices, monkey->_indices);
		EM->AddComponent<Engine::Transformable>("player", glm::vec3(0.0f, 0.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0, 2.0f, 2.0f));
		EM->AddComponent<Engine::AABB>("player");

		EM->AddComponent<Engine::Renderable>("box", box->_vertices, box->_indices);
		EM->AddComponent<Engine::Transformable>("box", glm::vec3(0.0f, -5.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0, 1.0f, 1.0f));
		EM->AddComponent<Engine::AABB>("box");

		player1->AddChild(test);

		trans = player1->GetComponent<Engine::Transformable>();

		precision = 1.0;
		Json::Value event;
		for (auto it : EM->GetEntities())
		{
			event["Entities"][it->GetName()];
			for (auto j : it->GetChildren())
			{
				event["Entities"][it->GetName()]["Child"] = j->GetName();

			}


		}
		Json::StyledWriter writer;
		std::string outputConfig = writer.write(event);

		std::cout << event;
	};

	virtual void Cleanup()  override {
		EM->Clear();
		SM->Clear();
	};

	virtual void Pause()  override {};

	virtual void Resume()  override {};

	virtual void Update(DeltaTime deltaTime)  override {
		float direction = 1.0f;
		Inputs::Input* inp = nullptr;
		if (inp->getKeyDown(VK_SHIFT)) { direction = -1.0f; };
		if (inp->getKeyDown(VK_CONTROL)) { precision += 0.1f*direction; };
		if (inp->getKeyDown(VK_LEFT)) { trans->Move(glm::vec3(precision*deltaTime*-5.0f, 0.0f, 0.0f)); }
		if (inp->getKeyDown(VK_RIGHT)) { trans->Move(glm::vec3(precision*deltaTime*5.0f, 0.0f, 0.0f)); }
		if (inp->getKeyDown(VK_UP)) { trans->Move(glm::vec3(0.0f, precision*deltaTime*5.0f, 0.0f)); }
		if (inp->getKeyDown(VK_DOWN)) { trans->Move(glm::vec3(0.0f, precision*deltaTime*-5.0f, 0.0f)); }
		if (inp->getKeyDown(VK_SPACE)) { trans->SetRotation(glm::vec3(45.0f, 45.0f, .0f)); }
		if (inp->getKeyDown('X')) { trans->Rotate(glm::vec3(precision*direction*deltaTime*25.0f, 0.0f, 0.0f)); }
		if (inp->getKeyDown('Y')) { trans->Rotate(glm::vec3(0.0f, precision*direction*deltaTime*25.0f, 0.0f)); }
		if (inp->getKeyDown('Z')) { trans->Rotate(glm::vec3(0.0f, 0.0f, precision*direction*deltaTime*25.0f)); }

		EM->Update(deltaTime);
		SM->Update(deltaTime);
	};

private:
	float precision;

	Camera* cam;

	Engine::EntityManager* EM;
	Engine::SystemManager* SM;

	std::shared_ptr<Engine::Entity> player1;
	std::shared_ptr<Engine::Entity> test;
	std::shared_ptr<Engine::Transformable> trans;
};

int main(int argc, char** argv) {
	window.createWindow("Dickbutt!", glm::vec2(600, 400), glm::vec2(0, 0), "Resources/Cursor.ico", "Resources/Cursor.ico", ENGINE_WINDOWED, WndProc);
	window.InitOpenGL();

	Engine::Time timer;
	Engine::SceneManager::GetInstance()->ChangeScene(new TestScene());

	while (window.IsOpen()) {

		DeltaTime dt = timer.Update();

		Engine::SceneManager::GetInstance()->Update(dt);

		window.getMessage();
	}

	window.Uninit();

	return 0;
}