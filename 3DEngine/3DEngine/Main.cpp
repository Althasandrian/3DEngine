#include "Core\Window.h"
#include "Core\Entity.hpp"
#include "Core\Component.hpp"
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "Core\Time.hpp"
#include "Core\Rendering\Renderer.h"

Window window;
std::vector<Engine::Entity> entities;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SETFOCUS:
		
		break;
	case WM_KILLFOCUS:

		break;
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

	window.createWindow("Dickbutt!", glm::vec2(600, 400), glm::vec2(0, 0), "Resources/Cursor.ico", "Resources/Cursor.ico", ENGINE_WINDOWED, WndProc);
	window.InitOpenGL();

	Engine::Time timer;
	std::vector<Engine::Renderable*> renderables;
	renderables.push_back(new Engine::Renderable());
	for (unsigned i = 0; i < renderables.size(); i++) {
		renderables[i]->Init();
	}
	Engine::Renderer::GetInstance()->Renderende(&window);

	while (window.IsOpen()) {

		timer.Update();

		Engine::Renderer::GetInstance()->Draw(renderables);

		window.getMessage();
	}

	window.Uninit();

	return 0;
}