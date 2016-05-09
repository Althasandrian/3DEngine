#ifndef Engine_Transformable_hpp
#define Engine_Transformable_hpp

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glew.h>

#include <Core/Managers/EntityManager.hpp>

namespace Engine
{
	class Transform : public Component
	{
	public:
		Transform(glm::vec3 pos = glm::vec3(0), glm::vec3 rot = glm::vec3(0), glm::vec3 scale = glm::vec3(0))
		: _position(pos), _rotation(glm::radians(rot)), _scale(scale) {};
		virtual ~Transform() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void SetPosition(glm::vec3 position);
		void Move(glm::vec3 move);
		void SetPositionWithoutChildren(glm::vec3 position);
		void MoveWithoutChildren(glm::vec3 move);

		void SetRotation(glm::vec3 rotation);
		void Rotate(glm::vec3 rotate);
		void SetRotationWithoutChildren(glm::vec3 rotation);
		void RotateWithoutChildren(glm::vec3 rotate);

		void Scale(GLfloat scale);
		void Scale(glm::vec3 scale);
		void ScaleWithoutChildren(GLfloat scale);
		void ScaleWithoutChildren(glm::vec3 scale);

		glm::vec3 const GetPosition();

		glm::vec3 const GetRotationRad();
		glm::vec3 const GetRotationDeg();

		glm::vec3 const GetScale();

	private:
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

	inline void Transform::Init() {}

	inline void Transform::Cleanup() {}

	inline void Transform::Update(DeltaTime deltaTime) {}

	///-----------------------------------------------------

	inline void Transform::SetPosition(glm::vec3 position) {
		glm::vec3 offset = _position - position;
		_position = position;
		this->MoveChildren(offset);
	};

	inline void Transform::Move(glm::vec3 move) {
		_position += move;
		this->MoveChildren(move);
	};

	inline void Transform::SetPositionWithoutChildren(glm::vec3 position) {
		_position = position;
	};

	inline void Transform::MoveWithoutChildren(glm::vec3 move) {
		_position += move;
	};

	///-----------------------------------------------------

	inline void Transform::SetRotation(glm::vec3 rotation) {
		_rotation = glm::radians(rotation);
		this->SetRotationChildren(rotation);
	};

	inline void Transform::Rotate(glm::vec3 rotate) {
		_rotation += glm::radians(rotate);
		this->RotateChildren(rotate);
	};

	inline void Transform::SetRotationWithoutChildren(glm::vec3 rotation) {
		_rotation = glm::radians(rotation);
	};

	inline void Transform::RotateWithoutChildren(glm::vec3 rotate) {
		_rotation += glm::radians(rotate);
	};

	///-----------------------------------------------------

	inline void Transform::Scale(GLfloat scale) {
		_scale *= glm::vec3(scale);
		this->ScaleChildren(scale);
	};

	inline void Transform::Scale(glm::vec3 scale) {
		_scale *= scale;
		this->ScaleChildren(scale);
	};

	inline void Transform::ScaleWithoutChildren(GLfloat scale) {
		_scale *= glm::vec3(scale);
	};

	inline void Transform::ScaleWithoutChildren(glm::vec3 scale) {
		_scale *= scale;
	};

	///-----------------------------------------------------

	inline glm::vec3 const Transform::GetPosition()		{ return _position; };
	inline glm::vec3 const Transform::GetRotationRad()	{ return _rotation; };
	inline glm::vec3 const Transform::GetRotationDeg()	{ return glm::degrees(_rotation); };
	inline glm::vec3 const Transform::GetScale()		{ return _scale; };

	///-----------------------------------------------------

	inline void Transform::MoveChildren(glm::vec3 move) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>();
			if (childTransform != nullptr) {
				childTransform->Move(move);
			}
		}
	};

	///-----------------------------------------------------

	inline void Transform::SetRotationChildren(glm::vec3 rotation) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>();
			if (childTransform != nullptr) {
				childTransform->SetRotation(rotation);

				//New position
			}
		}
	};

	inline void Transform::RotateChildren(glm::vec3 rotate) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>();
			if (childTransform != nullptr) {
				childTransform->Rotate(rotate);
				
				//glm::vec3 offset = this->GetPosition() - childTransform->GetPosition();
				//
				//childTransform->Move(offset);

				//glm::quat Qp = glm::quat(0.0f, offset);
				//glm::quat Qr = glm::quat(cos(childTransform->GetRotationRad() / 2.0f), sin(childTransform->GetRotationRad() / 2.0f));
				//glm::quat Qi = glm::inverse(Qr);

				//auto asd = Qi * Qp * Qr;

				//childTransform->Move(glm::vec3(asd.x, asd.y, asd.z));
			}
		}
	};

	///-----------------------------------------------------

	inline void Transform::ScaleChildren(GLfloat scale) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>();
			if (childTransform != nullptr) {
				childTransform->Scale(scale);
			}
		}
	};

	inline void Transform::ScaleChildren(glm::vec3 scale) {
		std::vector<std::shared_ptr<Entity>> children = _owner->GetChildren();
		for (std::shared_ptr<Entity> child : children) {
			std::shared_ptr<Transform> childTransform = child->GetComponent<Transform>();
			if (childTransform != nullptr) {
				childTransform->Scale(scale);
			}
		}
	};
}

#endif