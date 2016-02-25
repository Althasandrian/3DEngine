#include "Renderer.h"
#include <iostream>
#include <gl\GL.h>
#include <Windows.h>
#include <fstream>


namespace Engine
{
	void Renderer::Renderende(Window* window) {
		_window = window;

		glClearColor(0.0f, 0.25f, 0.25f, 0.0f);

		_GLSLP.AttachShader("Core/Rendering/Shaders/Vert.txt", GL_VERTEX_SHADER);
		_GLSLP.AttachShader("Core/Rendering/Shaders/Frag.txt", GL_FRAGMENT_SHADER);
	}

	void Renderer::Draw(std::vector<Engine::Renderable*> renderables) {
		_GLSLP.Use();

		glClear(GL_COLOR_BUFFER_BIT);

		for (unsigned i = 0; i < renderables.size(); i++) {
			renderables[i]->Draw();
		}
		
		SwapBuffers(_window->GetHDC());

		glUseProgram(0);
	}
}