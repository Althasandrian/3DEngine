#include "ShaderProgram.h"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\..\lib\Helper.hpp"

namespace Engine {
	GLSLProgram::GLSLProgram()
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	bool GLSLProgram::AttachShader(const char* source, GLenum shaderType) {
		_shaders.insert(std::make_pair(shaderType, new Shader()));
		_shaders[shaderType]->CompileShader(source, shaderType);

		_programHandle = glCreateProgram();

		GLAssert();

		glAttachShader(_programHandle, _shaders[shaderType]->GetShaderID());

		GLAssert();

		glLinkProgram(_programHandle);

		GLAssert();

		glm::mat4 ModelMatrix = glm::mat4(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 ViewMatrix = glm::translate(glm::vec3(-500.0f, 0.0f, 0.0f));
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), 1600.0f/900.0f, 0.1f, 1000.0f);
		MVP = ModelMatrix * ViewMatrix * projectionMatrix;

		SetUniform("MVP", MVP);

		GLAssert();

		glDetachShader(_programHandle, _shaders[shaderType]->GetShaderID());
		glDeleteShader(_shaders[shaderType]->GetShaderID());

		return true;
	}

	void GLSLProgram::Use(float windowRatio) {
		glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(0.0f, 600.0f, 400.0f, 0.0f, 200.0f, -200.0f);

		glUseProgram(_programHandle);
	}
}