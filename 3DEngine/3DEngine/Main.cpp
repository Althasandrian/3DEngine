﻿#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "Core\Window.h"
#include "Core\Time.hpp"
#include <glew.h>
#include <windows.h>
#include <Core\Input\Input.h>

float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
float movX = 0.0f, movY = 0.0f, movZ = 0.0f;

#include <lib\Helper.hpp>

#include <Core\Managers\EntityManager.hpp>
#include <Core\Managers\SystemManager.hpp>
#include <Core\Systems\RenderingSystem.hpp>


class asdasdasd : public Engine::Entity
{
public:
	asdasdasd() {};
	virtual ~asdasdasd() {};

	virtual void Init() { std::cout << "init" << std::endl; };
	virtual void Cleanup() { std::cout << "cleanup" << std::endl; };

	virtual void Update(Engine::DeltaTime deltaTime) { std::cout << "update" << std::endl; };
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

#ifdef _DEBUG
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif

	window.createWindow("Dickbutt!", glm::vec2(600, 400), glm::vec2(0, 0), "Resources/Cursor.ico", "Resources/Cursor.ico", ENGINE_FULLSCREEN, WndProc);
	window.InitOpenGL();

	Engine::SystemManager* SM = Engine::SystemManager::GetInstance();
	SM->AddSystem<Engine::RenderingSystem, Window*>(&window);

	Engine::Time timer;

	while (window.IsOpen()) {

		Engine::DeltaTime dt = timer.Update();

		Inputs::Input* inp;
		if (inp->getKeyDown(VK_LEFT)) { movX = -0.1f; }
		else if (inp->getKeyDown(VK_RIGHT)) { movX = 0.1f; }
		else if (inp->getKeyDown(VK_UP)) { movY = 0.1f; }
		else if (inp->getKeyDown(VK_DOWN)) { movY = -0.1f; }
		else if (inp->getKeyDown('Z')) { rotZ = 1.0f; }
		else if (inp->getKeyDown('X')) { rotX = 1.0f; }
		else if (inp->getKeyDown('Y')) { rotY = 1.0f; }
		else if (inp->getKeyDown('S')) { rotX = 0.0f; rotY = 0.0f; rotZ = 0.0f;	}
		else { movX = 0.0f; movY = 0.0f; }

		SM->Update(dt);

		window.getMessage();
	}

	window.Uninit();

	return 0;
}