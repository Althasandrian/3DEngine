#ifndef ShaderProgram_h
#define ShaderProgram_h

#include <Windows.h>
#include <glew.h>
#include <glm\glm.hpp>
#include <gl\GL.h>
#include <unordered_map>

#include "Shader.h"
#include "..\ResourceManager.h"

namespace Engine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();
		
		bool AttachShader(const char* source, GLenum shaderType);
		void Use(float windowRatio);

		int GetHandle();
		bool IsLinked();

		void BindAttribLocation(GLuint location, const char* name);
		void BindFragDataLocation(GLuint location, const char* name);

		template<class T> void SetUniform(const char* name, T tempType);

		void printActiveUniforms();
		void printActiveAttribs();
	private:
		size_t _programHandle;
		bool _linked;
		char* _logString;
		int _getUniformLocation(const char* name);
		bool _fileExists(const char* fileName);
		std::unordered_map<GLenum, Shader*> _shaders;
		glm::mat4 MVP;
	};

	template<class T> void GLSLProgram::SetUniform(const char* name, T tempType) {
		glUseProgram(_programHandle);

		GLint location = glGetUniformLocation(_programHandle, name);
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(tempType));

		glUseProgram(0);
	}
}

#endif