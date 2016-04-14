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

#include <Core/ResourceManager.h>


class player : public Engine::Entity
{
public:
	player(){};
	virtual ~player(){};

	void Init(){};
	void Cleanup(){};
	void Update(Engine::DeltaTime dt){};

	
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

int main(int argc, char** argv) {
	Engine::EntityManager* EM = Engine::EntityManager::GetInstance();
	
	window.createWindow("Dickbutt!", glm::vec2(600, 400), glm::vec2(0, 0), "Resources/Cursor.ico", "Resources/Cursor.ico", ENGINE_WINDOWED, WndProc);
	window.InitOpenGL();

	Engine::SystemManager* SM = Engine::SystemManager::GetInstance();
	SM->AddSystem<Engine::PhysicsSystem>();
	SM->AddSystem<Engine::RenderingSystem, Window*>(&window);

	std::shared_ptr<Engine::Entity> player1 = EM->AddEntity("player", std::make_shared<player>());
	std::shared_ptr<Engine::Entity> test = EM->AddEntity("box", std::make_shared<player>());

	Resource* monkey = ResourceManager::GetInstance()->LoadResource("Resources/Monkey.obj");
	Resource* box = ResourceManager::GetInstance()->LoadResource("Resources/Box.obj");

	EM->AddComponent<Engine::Renderable>("player", monkey->_vertices, monkey->_indices);
	EM->AddComponent<Engine::Transformable>("player", glm::vec3(0.0f, 0.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0, 2.0f, 2.0f));
	EM->AddComponent<Engine::AABB>("player");

	EM->AddComponent<Engine::Renderable>("box", box->_vertices, box->_indices);
	EM->AddComponent<Engine::Transformable>("box", glm::vec3(0.0f, 0.0f, -15.0f), glm::vec3(45.0f, 45.0f, 0.0f), glm::vec3(1.0, 1.0f, 1.0f));
	EM->AddComponent<Engine::AABB>("box");

	std::shared_ptr<Engine::Transformable> trans = player1->GetComponent<Engine::Transformable>();

	Engine::Time timer;

	float precision = 1.0;

	while (window.IsOpen()) {

		Engine::DeltaTime dt = timer.Update();
		float direction = 1.0f;
		Inputs::Input* inp = nullptr;
		if (inp->getKeyDown(VK_SHIFT)) { direction = -1.0f; };
		if (inp->getKeyDown(VK_CONTROL)) { precision += 0.1f*direction; };
		if (inp->getKeyDown(VK_LEFT)) { trans->Move(glm::vec3(precision*dt*-5.0f, 0.0f, 0.0f)); }
		if (inp->getKeyDown(VK_RIGHT)) { trans->Move(glm::vec3(precision*dt*5.0f, 0.0f, 0.0f)); }
		if (inp->getKeyDown(VK_UP)) { trans->Move(glm::vec3(0.0f, precision*dt*5.0f, 0.0f)); }
		if (inp->getKeyDown(VK_DOWN)) { trans->Move(glm::vec3(0.0f, precision*dt*-5.0f, 0.0f)); }
		if (inp->getKeyDown(VK_SPACE)) { trans->SetRotation(glm::vec3(45.0f, 45.0f, .0f)); }
		if (inp->getKeyDown('X')) { trans->Rotate(glm::vec3(precision*direction*dt*25.0f, 0.0f, 0.0f)); }
		if (inp->getKeyDown('Y')) { trans->Rotate(glm::vec3(0.0f, precision*direction*dt*25.0f, 0.0f)); }
		if (inp->getKeyDown('Z')) { trans->Rotate(glm::vec3(0.0f, 0.0f, precision*direction*dt*25.0f)); }

		EM->Update(dt);
		SM->Update(dt);

		window.getMessage();
	}

	EM->Clear();
	SM->Clear();
	window.Uninit();

	return 0;
}