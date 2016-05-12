#ifndef Engine_RenderingSystem_hpp
#define Engine_RenderingSystem_hpp

#include <chrono>

#include <glew.h>
#include <gl\GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Core/Shaders/ShaderProgram.hpp>
#include <Core/Managers/SystemManager.hpp>

#include <Core/Components/Transform.hpp>
#include <Core/Components/Render.hpp>
#include <Core/Components/Color.hpp>
#include <Core/Components/AABB.hpp>
#include <Core/Components/Shader.hpp>
#include <Core/Components/Texture.h>

#include <Core/Systems/Buffer.hpp>

#include <Core/Camera.hpp>

namespace Engine
{
	class RenderingSystem : public System
	{
	public:
		RenderingSystem(Window* window, const char* vertexShaderPath = "Resources/Vert.txt", const char* fragmentShaderPath = "Resources/Frag.txt")
			: _window(window), _defaultShader(new ShaderProgram), _cam(new Camera), System() {

			_defaultShader->CompileShader(vertexShaderPath, GL_VERTEX_SHADER);
			_defaultShader->CompileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
			GLAssert();
		};

		virtual ~RenderingSystem() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Pause() override;
		virtual void Resume() override;

		virtual void Update(DeltaTime deltaTime) override;

		void SetCamera(Camera* cam) { _cam = cam; };

	private:
		EntityManager* _entityManager;
		ShaderProgram* _defaultShader;
		Window* _window;

		Buffer _vertexBuffer;
		Buffer _indiceBuffer;

		Camera* _cam;
	};

	inline void RenderingSystem::Init() {
		_entityManager = EntityManager::GetInstance();

		_vertexBuffer.CreateBuffer(GL_ARRAY_BUFFER);
		_indiceBuffer.CreateBuffer(GL_ELEMENT_ARRAY_BUFFER);

		glEnable(GL_DEPTH_TEST);

		glUseProgram(0);

		glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
	};

	inline void RenderingSystem::Cleanup() {

	};

	inline void RenderingSystem::Pause() {
		if (!_paused) {
			_paused = true;
		}
	};

	inline void RenderingSystem::Resume() {
		if (_paused) {
			_paused = false;
		}
	};

	inline void RenderingSystem::Update(DeltaTime deltaTime) {
		if (!_paused) {

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			std::vector<std::shared_ptr<Entity>> entities = _entityManager->GetEntities();
			for (std::shared_ptr<Entity> entity : entities) {

				//Get components needded for rendering
				std::shared_ptr<Transform>	transform	= entity->GetComponent<Transform>();
				std::shared_ptr<Render>		render		= entity->GetComponent<Render>();
				std::shared_ptr<AABB>		aabb		= entity->GetComponent<AABB>();
				std::shared_ptr<Texture>	texture		= entity->GetComponent<Texture>();
				std::shared_ptr<Shader>		shader		= entity->GetComponent<Shader>();
				GLAssert();

				//Check for the bare minimum components needed for rendering
				if (transform != nullptr && render != nullptr) {

					//If entity has shader component use it. Otherwise use default shader
					GLuint shaderID;
					if (shader != nullptr)	{ shaderID = shader->GetProgramID(); }
					else					{ shaderID = _defaultShader->GetProgramID(); }
					glUseProgram(shaderID);
					GLAssert();

					//Get Data
					glm::mat4 Model = glm::translate(glm::mat4(1), transform->GetPosition());

					glm::mat4 Scale = glm::scale(glm::mat4(1), transform->GetScale());

					glm::mat4	Rotate = glm::rotate(glm::mat4(1), transform->GetRotationRad().x, glm::vec3(1.0f, 0.0f, 0.0f));
								Rotate = glm::rotate(Rotate, transform->GetRotationRad().y, glm::vec3(0.0f, 1.0f, 0.0f));
								Rotate = glm::rotate(Rotate, transform->GetRotationRad().z, glm::vec3(0.0f, 0.0f, 1.0f));

								Model = Model * Rotate * Scale;

					glm::mat4 View = _cam->GetViewMatrix();

					glm::mat4 Projection = glm::perspective(glm::radians(60.0f), _window->GetSize().x / _window->GetSize().y, 0.01f, 100.0f);

					glm::vec3 ViewPosition = _cam->Position;

					glm::vec3 LightPosition = glm::vec3(0.0f, 2.0f, -15.0f);
					GLAssert();

					//Bind Data
					if (texture != nullptr) {
						texture->BindTexture(shaderID);
					}

					_vertexBuffer.BindBufferData(render->GetVertexData().size(), &render->GetVertexData()[0].x);
					_indiceBuffer.BindBufferData(render->GetIndiceData().size(), &render->GetIndiceData()[0].x);
					GLAssert();

					GLuint ModelLocation = glGetUniformLocation(shaderID, "Model");
					GLuint ViewLocation = glGetUniformLocation(shaderID, "View");
					GLuint ProjectionLocation = glGetUniformLocation(shaderID, "Projection");
					GLuint ViewPositionLocation = glGetUniformLocation(shaderID, "ViewPosition");
					GLuint LightPositionLocation = glGetUniformLocation(shaderID, "LightPosition");
					GLAssert();

					GLuint PositionLocation = glGetAttribLocation(shaderID, "in_Position");
					GLuint TexCoordinateLocation = glGetAttribLocation(shaderID, "in_TexCoord");
					GLuint NormalLocation = glGetAttribLocation(shaderID, "in_Normal");
					GLAssert();

					glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));
					glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(View));
					glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, glm::value_ptr(Projection));
					glUniform3fv(ViewPositionLocation, 1, glm::value_ptr(ViewPosition));
					glUniform3fv(LightPositionLocation, 1, glm::value_ptr(LightPosition));
					GLAssert();

					if (PositionLocation != -1) {
						glEnableVertexAttribArray(PositionLocation);
						glVertexAttribPointer(PositionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3), (void*)(0 * sizeof(GLfloat)));
						GLAssert();
					} //if (PositionLocation != -1)

					if (TexCoordinateLocation != -1) {
						glEnableVertexAttribArray(TexCoordinateLocation);
						glVertexAttribPointer(TexCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3), (void*)(3 * sizeof(GLfloat)));
						GLAssert();
					} //if (TexCoordinateLocation != -1)

					if (NormalLocation != -1) {
						glEnableVertexAttribArray(NormalLocation);
						glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3), (void*)(6 * sizeof(GLfloat)));
						GLAssert();
					} //if (NormalLocation != -1)

					//Draw object
					glDrawElements(GL_TRIANGLES, render->GetIndiceData().size() * 3, GL_UNSIGNED_INT, (void*)0);
					GLAssert();

#ifdef DRAW_AABB
					if (aabb != nullptr) {
						_vertexBuffer.BindBufferData(aabb->GetVertexData().size(), &aabb->GetVertexData()[0].x);
						_indiceBuffer.BindBufferData(aabb->GetIndiceData().size(), &aabb->GetIndiceData()[0].x);

						Model = glm::translate(glm::mat4(1), transform->GetPosition());

						glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

						if (PositionLocation != -1) {
							glEnableVertexAttribArray(PositionLocation);
							glVertexAttribPointer(PositionLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(glm::vec3), (void*)(0 * sizeof(GLfloat)));
							GLAssert();
						} //if (PositionLocation != -1)

						glDrawElements(GL_LINE_STRIP, aabb->GetIndiceData().size() * 3, GL_UNSIGNED_INT, (void*)0);
					} //if (aabb != nullptr)
#endif // DRAW_AABB

				} //if (transform != nullptr && render != nullptr)
			} //for (std::shared_ptr<Entity> entity : entities)

			SwapBuffers(_window->GetHDC());
			glUseProgram(0);
			GLAssert();

		} //if (!_paused)
	};
}

#endif