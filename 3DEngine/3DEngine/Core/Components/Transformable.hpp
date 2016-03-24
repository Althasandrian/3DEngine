#ifndef Engine_Transformable_hpp
#define Engine_Transformable_hpp

#include <glm\glm.hpp>
#include <glew.h>

#include <Core/Managers/EntityManager.hpp>

namespace Engine
{
	class Transformable : public Component
	{
	public:
		Transformable(glm::vec3 pos = glm::vec3(0), glm::vec3 rot = glm::vec3(0), glm::vec3 scale = glm::vec3(0))
		: _position(pos), _rotation(rot), _scale(scale) {};
		virtual ~Transformable() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void SetPosition(glm::vec3 position) { _position = position; }
		void Move(glm::vec3 move) { _position += move; }

		void SetRotation(glm::vec3 rotation) { _rotation = rotation; }
		void Rotate(glm::vec3 rotate) { _rotation += rotate; }

		void Scale(GLfloat scale) { _scale *= glm::vec3(scale); }
		void Scale(glm::vec3 scale) { _scale *= scale; }
	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;
	};

	void Transformable::Init() {}

	void Transformable::Cleanup() {}

	void Transformable::Update(DeltaTime deltaTime) {}
}

#endif