#ifndef Engine_RenderingSystem_hpp
#define Engine_RenderingSystem_hpp

#include <chrono>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <Core\Managers\SystemManager.hpp>
#include <Core\Shaders\ShaderProgram.hpp>

#include <Core/Components/Renderable.hpp>
#include <Core/Components/Color.hpp>

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
		EntityManager* _entityManager;
		ShaderProgram* _default;
		Window* _window;

		glm::mat4 trans;
		glm::mat4 view;
		glm::mat4 proj;

		long long unsigned int _size;
		long long unsigned int _elemSize;
		std::vector<float> vertices;
		std::vector<float> colors;
		std::vector<GLuint> elements;
	};

	inline void RenderingSystem::Init() {
		std::cout << "Renderer Init();" << std::endl;
		_entityManager = EntityManager::GetInstance();
		_default = new ShaderProgram;
		_default->CompileShader("Core/Shaders/Vert.txt", GL_VERTEX_SHADER);
		_default->CompileShader("Core/Shaders/Frag.txt", GL_FRAGMENT_SHADER);

		vertices = std::static_pointer_cast<Renderable>(_entityManager->GetComponents<Renderable>("player").back())->GetVertexData();

		colors = std::static_pointer_cast<Color>(_entityManager->GetComponents<Color>("player").back())->GetColorData();

		glEnable(GL_DEPTH_TEST);

		glUseProgram(_default->GetProgramID());

		_size = vertices.size() * sizeof(float);
		_elemSize = elements.size();

		GLuint vertex;
		glGenBuffers(1, &vertex);
		glBindBuffer(GL_ARRAY_BUFFER, vertex);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		GLint posAttrib = glGetAttribLocation(_default->GetProgramID(), "in_Position");
		glEnableVertexAttribArray(posAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, vertex);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		GLuint color;
		glGenBuffers(1, &color);
		glBindBuffer(GL_ARRAY_BUFFER, color);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], GL_STATIC_DRAW);

		GLint colAttrib = glGetAttribLocation(_default->GetProgramID(), "in_Color");
		glEnableVertexAttribArray(colAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, color);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		GLuint ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elemSize*sizeof(GLuint), &elements[0], GL_STATIC_DRAW);

		//trans = glm::translate(trans, glm::vec3(0.5f, -1.0f, -0.5f));

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

			trans = glm::rotate(trans, rotX * 50 * (float)deltaTime * glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			trans = glm::rotate(trans, rotY * 50 * (float)deltaTime * glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			trans = glm::rotate(trans, rotZ * 50 * (float)deltaTime * glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			trans = glm::translate(trans, glm::vec3(movX, movY, movZ));

			GLint uniTrans = glGetUniformLocation(_default->GetProgramID(), "trans");
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//glDrawArrays(GL_TRIANGLES, 0, _size);
			glDrawElements(GL_TRIANGLES, _elemSize*sizeof(GLuint), GL_UNSIGNED_INT, (void*)0);

			SwapBuffers(_window->GetHDC());

			glUseProgram(0);
		}
	};
}

#endif