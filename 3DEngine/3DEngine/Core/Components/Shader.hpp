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
		Shader(const char* vertexSource, const char* fragmentSource);
		Shader();
		virtual ~Shader();

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void CompileShader(const char* source, GLenum shaderType);

		void BindShader();

		GLuint GetProgramID() { return _programID; }

	private:
		GLuint _programID;
	};

	inline Shader::Shader(const char* vertexSource, const char* fragmentSource) {
		_programID = glCreateProgram();

		CompileShader(vertexSource, GL_VERTEX_SHADER);
		CompileShader(fragmentSource, GL_FRAGMENT_SHADER);
	};

	inline Shader::Shader() {
		_programID = glCreateProgram();
	};

	inline Shader::~Shader() {};

	inline void Shader::Init() {};

	inline void Shader::Cleanup() {
		glDeleteShader(_programID);
	};

	inline void Shader::Update(DeltaTime deltaTime) {};

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

	inline void Shader::BindShader() {

	};
};

#endif