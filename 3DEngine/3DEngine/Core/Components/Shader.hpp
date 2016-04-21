#ifndef Engine_Shader_hpp
#define Engine_Shader_hpp

#include <glew.h>
#include <gl/GL.h>
#include <Core/ResourceManager.h>

#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Shader : public Component
	{
	public:
		Shader() { _programID = glCreateProgram(); };
		virtual ~Shader() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void CompileShader(const char* source, GLenum shaderType);

		GLuint GetProgramID() { return _programID; }

	private:
		GLuint _programID;
	};

	void Shader::Init() {}

	void Shader::Cleanup() {}

	void Shader::Update(DeltaTime deltaTime) {}

	inline void Shader::CompileShader(const char* source, GLenum shaderType) {
		Resource* asd = ResourceManager::GetInstance()->LoadResource(source);

		std::string temp = asd->getTextData();
		const char* fuck = temp.c_str();

		GLuint shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &fuck, 0);

		glCompileShader(shaderID);

		glAttachShader(_programID, shaderID);

		glLinkProgram(_programID);
	};
};

#endif