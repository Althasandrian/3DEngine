#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "Core\Window.h"
#include "Core\Entity.hpp"
#include "Core\Component.hpp"
#include "Core\Time.hpp"
#include "Core\Rendering\Renderer.h"
#include "Core\EntityManager.hpp"
Window window;
std::vector<Engine::Entity> entities;
std::vector<Engine::Renderable*> renderables;

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

	Engine::EntityManager* EM = Engine::EntityManager::GetInstance();

	std::shared_ptr<Engine::Entity> asd = std::make_shared<Engine::Entity>();
	asd->AddComponent(std::make_shared<Engine::Transformable>());

	std::shared_ptr<Engine::Entity> sad = std::make_shared<Engine::Entity>();
	sad->AddComponent(std::make_shared<Engine::Transformable>());

	std::shared_ptr<Engine::Entity> das = std::make_shared<Engine::Entity>();
	das->AddComponent(std::make_shared<Engine::Renderable>());
	
	EM->AddEntity(asd);
	EM->AddEntity(sad);
	EM->AddEntity(das);

	std::vector <std::shared_ptr <Engine::Transformable>> wolololo = EM->GetComponents<Engine::Transformable>();



	window.createWindow("Dickbutt!", glm::vec2(600, 400), glm::vec2(0, 0), "Resources/Cursor.ico", "Resources/Cursor.ico", ENGINE_WINDOWED, WndProc);
	window.InitOpenGL();

	Engine::Time timer;
	
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