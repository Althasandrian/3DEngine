#include "Renderer.h"
#include <iostream>
#include <glm\gtc\type_ptr.hpp>
#include <gl\GL.h>
#include <Windows.h>
#include <fstream>
#include "..\..\lib\Helper.hpp"


namespace Engine
{
	void Renderer::Renderende(Window* window) {
		_window = window;

		glClearColor(0.0f, 0.25f, 0.25f, 0.0f);

		//_GLSLP.AttachShader("Core/Rendering/Shaders/Vert.txt", GL_VERTEX_SHADER);
		//_GLSLP.AttachShader("Core/Rendering/Shaders/Frag.txt", GL_FRAGMENT_SHADER);

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream("Core/Rendering/Shaders/Vert.txt", std::ios::in);
		if (VertexShaderStream.is_open()){
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else{
			printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", "Core/Rendering/Shaders/Vert.txt");
			getchar();
		}
		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream("Core/Rendering/Shaders/Frag.txt", std::ios::in);
		if (FragmentShaderStream.is_open()){
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
		GLint Result = GL_FALSE;
		int InfoLogLength;
		// Compile Vertex Shader
		printf("Compiling shader : %s\n", "Core/Rendering/Shaders/Vert.txt");
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);
		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0){
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}
		// Compile Fragment Shader
		printf("Compiling shader : %s\n", "Core/Rendering/Shaders/Frag.txt");
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);
		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0){
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}
		// Link the program
		printf("Linking program\n");
		ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);
		// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0){
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}
		glDetachShader(ProgramID, VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		glUseProgram(ProgramID);

		glm::mat4 ViewMatrix = glm::translate(glm::vec3(-3.0f, 0.0f, 0.0f));
		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(ProgramID, "View"), 1, false, glm::value_ptr(ViewMatrix));

		glUniformMatrix4fv(glGetUniformLocation(ProgramID, "Projection"), 1, false, glm::value_ptr(ProjectionMatrix));

		glUseProgram(0);

		GLAssert();
	}

	void Renderer::Draw(std::vector<Engine::Renderable*> renderables) {
		//_GLSLP.Use(1600/900);
		glUseProgram(ProgramID);

		glMatrixMode(GL_PROJECTION);

		glClear(GL_COLOR_BUFFER_BIT);

		GLAssert();

		for (unsigned i = 0; i < renderables.size(); i++) {
			renderables[i]->Draw();
		}

		GLAssert();

		glRotatef(1.0f, 0.0f, 1.0f, 1.0f);

		GLAssert();

		SwapBuffers(_window->GetHDC());

		GLAssert();

		glUseProgram(0);

		GLAssert();
	}
}