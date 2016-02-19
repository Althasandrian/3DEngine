#include "Core\Window.h"
#include "Core\Entity.hpp"
#include "Core\Component.hpp"
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "Core\Time.hpp"

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

	float VertexPositions[] =
	{
		0.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
	};

	Engine::Time timer;

	Engine::Entity asd;

	asd.AddComponent(std::make_shared<Engine::Transformable>());
	asd.AddComponent(std::make_shared<Engine::Renderable>());
	std::shared_ptr<Engine::Transformable> das = asd.GetComponent<Engine::Transformable>();

	SetCursorPos(window.GetSize().x / 2, window.GetSize().y/2);

	while (window.IsOpen()) {

		timer.Update();

		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glVertexAttribPointer(0, 4, GL_FLOAT, 0, 0, VertexPositions);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glRotatef(1, 0, 0, 1.0);

		SwapBuffers(window.GetHDC());

		window.getMessage();
	}

	window.Uninit();

	return 0;
}