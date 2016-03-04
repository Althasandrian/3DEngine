#include "Shader.h"
#include "..\..\lib\Helper.hpp"

namespace Engine {
	Shader::Shader() {}

	Shader::~Shader() {}

	bool Shader::CompileShader(const char* source, GLenum shaderType) {
		Resource* shader = ResourceManager::GetInstance()->LoadResource(source);

		_shaderID = glCreateShader(shaderType);

		GLAssert();

		std::string tempString = shader->getTextData();
		const char* c_str = tempString.c_str();
		const GLint length = tempString.size();

		glShaderSource(_shaderID, 1, &c_str, &length);

		GLAssert();

		glCompileShader(_shaderID);

		GLAssert();

		int iCompilationStatus;
		glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &iCompilationStatus);

		GLAssert();

		if (iCompilationStatus == GL_FALSE) { return false; }

		_shaderType = shaderType;

		GLAssert();

		return true;
	}
}