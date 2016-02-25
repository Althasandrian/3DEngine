#include "ShaderProgram.h"

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

		glAttachShader(_programHandle, _shaders[shaderType]->GetShaderID());

		glLinkProgram(_programHandle);

		return true;
	}

	void GLSLProgram::Use() {
		glUseProgram(_programHandle);
	}
}