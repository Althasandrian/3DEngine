#ifndef Engine_RenderingSystem_hpp
#define Engine_RenderingSystem_hpp

#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Core/Shaders/ShaderProgram.hpp>
#include <Core/Managers/SystemManager.hpp>

#include <Core/Components/Transformable.hpp>
#include <Core/Components/Renderable.hpp>
#include <Core/Components/Color.hpp>

#include <Core/Systems/Buffer.hpp>

namespace Engine
{
	class RenderingSystem : public System
	{
	public:
		RenderingSystem(Window* window) : _window(window), System() {};
		virtual ~RenderingSystem() {};

		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void Update(DeltaTime deltaTime);

	private:
		void ResizeBuffer();

		EntityManager* _entityManager;
		ShaderProgram* _default;
		Window* _window;

		Buffer _vertexBuffer;
		Buffer _indiceBuffer;

		glm::mat4 rotate;
		glm::mat4 trans;
		glm::mat4 view;
		glm::mat4 proj;
	};

	inline void RenderingSystem::Init() {

		_vertexBuffer.CreateBuffer(GL_ARRAY_BUFFER);
		_indiceBuffer.CreateBuffer(GL_ELEMENT_ARRAY_BUFFER);

		_entityManager = EntityManager::GetInstance();

		_default = new ShaderProgram;
		_default->CompileShader("Core/Shaders/Vert.txt", GL_VERTEX_SHADER);
		_default->CompileShader("Core/Shaders/Frag.txt", GL_FRAGMENT_SHADER);

		glEnable(GL_DEPTH_TEST);

		glUseProgram(_default->GetProgramID());

		GLint posAttrib = glGetAttribLocation(_default->GetProgramID(), "in_Position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		GLint colAttrib = glGetAttribLocation(_default->GetProgramID(), "in_Color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		GLint uniView = glGetUniformLocation(_default->GetProgramID(), "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

		proj = glm::perspective(glm::radians(45.0f), 6.0f / 4.0f, 1.0f, 100.0f);
		GLint uniProj = glGetUniformLocation(_default->GetProgramID(), "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

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
			glUseProgram(_default->GetProgramID());
			GLAssert();

			std::vector<std::shared_ptr<Entity>> _entities = _entityManager->GetEntities();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto it = _entities.begin(); it != _entities.end(); it++) {

				auto renderable = it->get()->GetComponent<Renderable>();
				auto transformable = it->get()->GetComponent<Transformable>();

				if (renderable != nullptr && transformable != nullptr) {
					trans = glm::mat4(1);
					rotate = glm::mat4(1);

					_vertexBuffer.BindBufferData(renderable->GetVertexData().size(), &renderable->GetVertexData()[0].x);
					_indiceBuffer.BindBufferData(renderable->GetIndiceData().size(), &renderable->GetIndiceData()[0].x);
					GLAssert();

					//Parent-Child Tranformation
					std::vector<std::shared_ptr<Entity>> parents;
					auto parent = it->get()->GetParent();
					if (parent != nullptr) {
						parents.push_back(parent);
						while (parent->GetParent() != nullptr) {
							parent = parent->GetParent();
							parents.push_back(parent);
						}

						for (int i = parents.size()-1; i >= 0; --i) {
							std::cout << i << std::endl;
							auto parentTrans = parents[i]->GetComponent<Transformable>();
							if (parentTrans != nullptr) {
								trans = glm::translate(trans, *parentTrans->GetPosition());

								trans = glm::rotate(trans, parentTrans->GetRotation()->x, glm::vec3(1.0f, 0.0f, 0.0f));
								trans = glm::rotate(trans, parentTrans->GetRotation()->y, glm::vec3(0.0f, 1.0f, 0.0f));
								trans = glm::rotate(trans, parentTrans->GetRotation()->z, glm::vec3(0.0f, 0.0f, 1.0f));
								GLAssert();
							}
						}
					}

					rotate = glm::rotate(rotate, transformable->GetRotation()->x, glm::vec3(1.0f, 0.0f, 0.0f));
					rotate = glm::rotate(rotate, transformable->GetRotation()->y, glm::vec3(0.0f, 1.0f, 0.0f));
					rotate = glm::rotate(rotate, transformable->GetRotation()->z, glm::vec3(0.0f, 0.0f, 1.0f));
					GLAssert();

					trans = glm::translate(trans, *transformable->GetPosition());

					trans = trans * rotate;
					GLAssert();

					GLint uniTrans = glGetUniformLocation(_default->GetProgramID(), "trans");
					glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
					GLAssert();

					glDrawElements(GL_TRIANGLES, renderable->GetIndiceData().size() * 3, GL_UNSIGNED_INT, (void*)0);
					GLAssert();

				}
			}

			SwapBuffers(_window->GetHDC());
			GLAssert();

			glUseProgram(0);
			GLAssert();
		}
	};
}

#endif