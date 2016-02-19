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

float VertexPositions[] =
{
	0.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f,
};

void Draw() {
	
}

int main(int argc, char** argv) {

#ifdef _DEBUG
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif

	window.createWindow("Dickbutt!", glm::vec2(800, 600), glm::vec2(0, 0), "Resources/Cursor.ico", "Resources/Cursor.ico", ENGINE_WINDOWED, WndProc);
	window.InitOpenGL();

	Engine::Time timer;

	Engine::Entity asd;

	asd.AddComponent(std::make_shared<Engine::Transformable>());
	asd.AddComponent(std::make_shared<Engine::Renderable>());
	std::shared_ptr<Engine::Transformable> das = asd.GetComponent<Engine::Transformable>();

	SetCursorPos(window.GetSize().x / 2, window.GetSize().y/2);

	Engine::Renderer::GetInstance()->RegisterDraw(Draw);

	glClearColor(0.0f, 0.5f, 0.0f, 0.0f);

	std::vector<Engine::Renderable*> renderables;
	renderables.push_back(new Engine::Renderable());
	renderables[0]->Init();

	Engine::Renderer::GetInstance()->Renderende(&window);

	while (window.IsOpen()) {

		timer.Update();

		Engine::Renderer::GetInstance()->Draw(renderables);

		window.getMessage();
	}

	window.Uninit();

	return 0;
}