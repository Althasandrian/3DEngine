#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "Core/Window.h"
#include "Core/Time.hpp"
#include <glew.h>
#include <windows.h>
#include <Core/Input/Input.h>

float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
float movX = 0.0f, movY = 0.0f, movZ = 0.0f;

#include <lib/Helper.hpp>

#include <Core/Managers/EntityManager.hpp>
#include <Core/Managers/SystemManager.hpp>
#include <Core/Systems/RenderingSystem.hpp>

#include <Core/Components/Renderable.hpp>
#include <Core/Components/Color.hpp>

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
	SM->AddSystem<Engine::RenderingSystem, Window*>(&window);

	std::shared_ptr<Engine::Entity> const player1 = EM->AddEntity("player1", std::make_shared<player>());
	std::shared_ptr<Engine::Entity> const player2 = EM->AddEntity("player2", std::make_shared<player>());

	Resource* sad = ResourceManager::GetInstance()->LoadResource("Resources/asdasd.obj");
	Resource* asd = ResourceManager::GetInstance()->LoadResource("Resources/Dickbutt.obj");

	EM->AddComponent<Engine::Renderable>("player2", sad->_vertices, sad->_indices);
	EM->AddComponent<Engine::Color>("player2", sad->_vertices);
	EM->AddComponent<Engine::Transformable>("player2", glm::vec3(1.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	EM->AddComponent<Engine::Renderable>("player1", asd->_vertices, asd->_indices);
	EM->AddComponent<Engine::Color>("player1", asd->_vertices);
	EM->AddComponent<Engine::Transformable>("player1", glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	
	std::shared_ptr<Engine::Transformable> trans = player1->GetComponent<Engine::Transformable>();

	Engine::Time timer;

	while (window.IsOpen()) {

		Engine::DeltaTime dt = timer.Update();

		float asd = 0.1;
		Inputs::Input* inp = nullptr;
		if (inp->getKeyDown(VK_SHIFT)) { asd = -0.1; };
		if (inp->getKeyDown(VK_LEFT)) { trans->Move(glm::vec3(-0.1f, 0.0f, 0.0f)); }
		if (inp->getKeyDown(VK_RIGHT)) { trans->Move(glm::vec3(0.1f, 0.0f, 0.0f)); }
		if (inp->getKeyDown(VK_UP)) { trans->Move(glm::vec3(0.0f, 0.0f, -0.1f)); }
		if (inp->getKeyDown(VK_DOWN)) { trans->Move(glm::vec3(0.0f, 0.0f, 0.1f)); }
		if (inp->getKeyDown('X')) { trans->Rotate(glm::vec3(asd*1.0f, 0.0f, 0.0f)); }
		if (inp->getKeyDown('Y')) { trans->Rotate(glm::vec3(0.0f, asd*1.0f, 0.0f)); }
		if (inp->getKeyDown('Z')) { trans->Rotate(glm::vec3(0.0f, 0.0f, asd*1.0f)); }

		EM->Update(dt);
		SM->Update(dt);

		window.getMessage();
	}

	EM->Clear();
	SM->Clear();
	window.Uninit();

	return 0;
}