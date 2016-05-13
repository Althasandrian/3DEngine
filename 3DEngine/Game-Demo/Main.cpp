#include <Core/Engine.h>

Window window;

//Scenes
#include "GameScene.hpp"
#include "MainMenuScene.hpp"
#include "SplashScreenScene.hpp"

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
	window.createWindow("Game-Demo!", glm::vec2(1920, 1080), glm::vec2(0, 0), "Resources/Cursor.ico", "Resources/Cursor.ico", ENGINE_FULLSCREEN, WndProc);
	window.InitOpenGL();

	Engine::Time timer;
	Engine::SceneManager::GetInstance()->ChangeScene(new GameScene());

	while (window.IsOpen()) {

		DeltaTime dt = timer.Update();

		Engine::SceneManager::GetInstance()->Update(dt);

		window.getMessage();
	}

	window.Uninit();

	return 0;
}