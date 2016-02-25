#include "Shader.h"

namespace Engine {
	Shader::Shader() {

	}

	Shader::~Shader() {

	}

	bool Shader::CompileShader(const char* source, GLenum shaderType) {
		Resource* shader = ResourceManager::GetInstance()->LoadResource(source);

		_shaderID = glCreateShader(shaderType);

		std::string tempString = shader->getTextData();
		const char* c_str = tempString.c_str();
		const GLint length = tempString.size();

		glShaderSource(_shaderID, 1, &c_str, &length);
		glCompileShader(_shaderID);

		int iCompilationStatus;
		glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &iCompilationStatus);

		if (iCompilationStatus == GL_FALSE) { return false; }

		_shaderType = shaderType;

		return true;
	}
}