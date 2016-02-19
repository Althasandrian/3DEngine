#include "Renderer.h"
#include <iostream>
#include <gl\GL.h>
#include <Windows.h>
#include <fstream>

namespace Engine
{
	void Renderer::Renderende(Window* window) {
		_window = window;

		glClearColor(0.0f, 0.25f, 0.0f, 0.0f);

		_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vertData =	"#version 140									\n"
								"in  vec3 in_Position;							\n"
								"in  vec3 in_Color;								\n"
								"out vec3 ex_Color;								\n"
								"void main(void)								\n"
								"{												\n"
								"	gl_Position = vec4(in_Position, 1.0);		\n"
								"	ex_Color = in_Color;						\n"
								"}												\n";

		const char* fragData =	"#version 140									\n"
								"in  vec3 ex_Color;								\n"
								"out vec4 out_Color;							\n"
								"void main(void)								\n"
								"{												\n"
								"	out_Color = vec4(ex_Color, 1.0);			\n"
								"}												\n";

		glShaderSource(_vertexShader, 1, &vertData, 0);
		glShaderSource(_fragmentShader, 1, &fragData, 0);

		glCompileShader(_vertexShader);
		glCompileShader(_fragmentShader);

		_shaderProgram = glCreateProgram();

		glAttachShader(_shaderProgram, _vertexShader);
		glAttachShader(_shaderProgram, _fragmentShader);

		glLinkProgram(_shaderProgram);
	}

	void Renderer::Draw(std::vector<Engine::Renderable*> renderables) {
		glUseProgram(_shaderProgram);

		glClear(GL_COLOR_BUFFER_BIT);

		for (unsigned i = 0; i < renderables.size(); i++) {
			renderables[i]->Draw();
		}
		
		SwapBuffers(_window->GetHDC());

		glUseProgram(0);
	}
}