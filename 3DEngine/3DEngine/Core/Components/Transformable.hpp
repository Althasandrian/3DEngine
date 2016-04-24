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
		: _position(pos), _rotation(glm::radians(rot)), _scale(scale) {};
		virtual ~Transformable() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void SetPosition(glm::vec3 position);
		void Move(glm::vec3 move);

		void SetRotation(glm::vec3 rotation);
		void Rotate(glm::vec3 rotate);

		void Scale(GLfloat scale);
		void Scale(glm::vec3 scale);

		glm::vec3 const GetPosition();
		glm::vec3 const GetRotation();
		glm::vec3 const GetScale();

	private:
		void SetPositionChildren(glm::vec3 position);
		void MoveChildren(glm::vec3 move);

		void SetRotationChildren(glm::vec3 rotation);
		void RotateChildren(glm::vec3 rotate);

		void ScaleChildren(GLfloat scale);
		void ScaleChildren(glm::vec3 scale);

	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;
	};

	inline void Transformable::Init() {}

	inline void Transformable::Cleanup() {}

	inline void Transformable::Update(DeltaTime deltaTime) {}

	///-----------------------------------------------------

	inline void Transformable::SetPosition(glm::vec3 position) {
		_position = position;
		this->SetPositionChildren(position);
	};

	inline void Transformable::Move(glm::vec3 move) {
		_position += move;
		this->MoveChildren(move);
	};

	///-----------------------------------------------------

	inline void Transformable::SetRotation(glm::vec3 rotation) {
		_rotation = glm::radians(rotation);
		this->SetRotationChildren(rotation);
	};

	inline void Transformable::Rotate(glm::vec3 rotate) {
		_rotation += glm::radians(rotate);
		this->RotateChildren(rotate);
	};

	///-----------------------------------------------------

	inline void Transformable::Scale(GLfloat scale) {
		_scale *= glm::vec3(scale);
		this->ScaleChildren(scale);
	};

	inline void Transformable::Scale(glm::vec3 scale) {
		_scale *= scale;
		this->ScaleChildren(scale);
	};

	///-----------------------------------------------------

	inline glm::vec3 const Transformable::GetPosition()	{ return _position; };
	inline glm::vec3 const Transformable::GetRotation()	{ return _rotation; };
	inline glm::vec3 const Transformable::GetScale()		{ return _scale; };

	///-----------------------------------------------------

	inline void Transformable::SetPositionChildren(glm::vec3 position) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transformable> childTransform = child->GetComponent<Transformable>();
			if (childTransform != nullptr) {
				//Calculate position offset
				//childTransform->SetPosition(position);
			}
		}
	};

	inline void Transformable::MoveChildren(glm::vec3 move) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transformable> childTransform = child->GetComponent<Transformable>();
			if (childTransform != nullptr) {
				childTransform->Move(move);
			}
		}
	};

	///-----------------------------------------------------

	inline void Transformable::SetRotationChildren(glm::vec3 rotation) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transformable> childTransform = child->GetComponent<Transformable>();
			if (childTransform != nullptr) {
				childTransform->SetRotation(rotation);
				//Calculate new position based on rotation
			}
		}
	};

	inline void Transformable::RotateChildren(glm::vec3 rotate) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transformable> childTransform = child->GetComponent<Transformable>();
			if (childTransform != nullptr) {
				childTransform->Rotate(rotate);
				//Calculate new position based on rotation
			}
		}
	};

	///-----------------------------------------------------

	inline void Transformable::ScaleChildren(GLfloat scale) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transformable> childTransform = child->GetComponent<Transformable>();
			if (childTransform != nullptr) {
				childTransform->Scale(scale);
			}
		}
	};

	inline void Transformable::ScaleChildren(glm::vec3 scale) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transformable> childTransform = child->GetComponent<Transformable>();
			if (childTransform != nullptr) {
				childTransform->Scale(scale);
			}
		}
	};
}

#endif