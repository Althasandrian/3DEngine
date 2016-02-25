#ifndef Shader_h
#define Shader_h

#include <Windows.h>
#include <glew.h>
#include <glm\glm.hpp>
#include <gl\GL.h>

#include "..\ResourceManager.h"

namespace Engine {
	class Shader
	{
	public:
		Shader();
		~Shader();

		bool CompileShader(const char* source, GLenum shaderType);
		GLuint GetShaderID() { return _shaderID; }
	private:
		GLuint _shaderID;
		GLenum _shaderType;
	};
}

#endif