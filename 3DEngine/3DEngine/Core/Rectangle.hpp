#ifndef ENGINE_Rectangle_hpp
#define ENGINE_Rectangle_hpp

#include <glew.h>
#include <glm/glm.hpp>

#include <Core/Managers/EntityManager.hpp>

#include <Core/Components/Transform.hpp>
#include <Core/Components/Render.hpp>
#include <Core/Components/AABB.hpp>

namespace Engine
{
	class Rectangle : public Entity
	{
	public:
		Rectangle(std::string name, glm::vec2 position, glm::vec2 size, GLfloat depth);
		virtual ~Rectangle();

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

	private:
		std::shared_ptr<Transform>	_transform;
		std::shared_ptr<Render>		_render;
		std::shared_ptr<AABB>		_aabb;

		std::string					_name;
		glm::vec2					_position;
		glm::vec2					_size;
		GLfloat						_depth;
	};

	inline Rectangle::Rectangle(std::string name, glm::vec2 position, glm::vec2 size, GLfloat depth)
		: _name(name), _position(position), _size(size), _depth(depth), Entity()
	{

	};

	inline Rectangle::~Rectangle()
	{
	};

	inline void Rectangle::Init() {
		std::vector<glm::vec3> vertices = {
			glm::vec3(-(_size.x / 2.0f), -(_size.y / 2.0f), _depth),
			glm::vec3(1.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3( (_size.x / 2.0f), -(_size.y / 2.0f), _depth),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(-(_size.x / 2.0f),  (_size.y / 2.0f), _depth),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3( (_size.x / 2.0f),  (_size.y / 2.0f), _depth),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f)
		};

		std::vector<glm::uvec3> indices = {
			glm::vec3(0, 1, 2),
			glm::vec3(1, 3, 2)
		};

		EntityManager* EM = EntityManager::GetInstance();

		EM->AddComponent<Transform>(this->_name, glm::vec3(_position, _depth));
		EM->AddComponent<Render>(this->_name, vertices, indices);
		EM->AddComponent<AABB>(this->_name);

		_transform = EM->GetEntity(this->_name)->GetComponent<Transform>();
		_render = EM->GetEntity(this->_name)->GetComponent<Render>();
		_aabb = EM->GetEntity(this->_name)->GetComponent<AABB>();
	};

	inline void Rectangle::Cleanup() {

	};

	inline void Rectangle::Update(DeltaTime deltaTime) {

	};
}

#endif