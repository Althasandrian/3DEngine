#ifndef Engine_PhysicsSystem_hpp
#define Engine_PhysicsSystem_hpp

#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Core/Shaders/ShaderProgram.hpp>
#include <Core/Managers/SystemManager.hpp>

#include <Core/Components/Transformable.hpp>
#include <Core/Components/Renderable.hpp>
#include <Core/Components/Color.hpp>
#include <Core/Components/AABB.hpp>

#include <Core/Systems/Buffer.hpp>

namespace Engine
{
	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem() : System() {};
		virtual ~PhysicsSystem() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Pause() override;
		virtual void Resume() override;

		virtual void Update(DeltaTime deltaTime) override;

		void UpdateAABB();
	private:
		EntityManager* _entityManager;
	};

	inline void PhysicsSystem::Init() {

	};

	inline void PhysicsSystem::Cleanup() {

	};

	inline void PhysicsSystem::Pause() {

	};

	inline void PhysicsSystem::Resume() {

	};

	inline void Update(DeltaTime deltaTime) {

	};

	inline void UpdateAABB() {

	};
}

#endif