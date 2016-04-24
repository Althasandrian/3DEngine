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
	private:
		EntityManager* _entityManager;
	};

	inline void PhysicsSystem::Init() {
		_entityManager = EntityManager::GetInstance();
	};

	inline void PhysicsSystem::Cleanup() {

	};

	inline void PhysicsSystem::Pause() {

	};

	inline void PhysicsSystem::Resume() {

	};

	inline void PhysicsSystem::Update(DeltaTime deltaTime) {
		std::vector<std::shared_ptr<Entity>> entities = _entityManager->GetEntities();
		for (auto it = entities.begin(); it != entities.end(); it++) {
			auto transformable = it->get()->GetComponent<Transformable>();
			auto renderable = it->get()->GetComponent<Renderable>();
			auto aabb = it->get()->GetComponent<AABB>();

			if (transformable != nullptr && renderable != nullptr) {
				glm::mat4 scale = glm::mat4(1);
				glm::mat4 rotation = glm::mat4(1);
				glm::mat4 position = glm::mat4(1);

				std::vector<glm::vec3> vertexData = renderable->GetVertexData();
				std::vector<glm::vec4> transVertDat;

				scale = glm::scale(scale, transformable->GetScale());

				rotation = glm::rotate(rotation, transformable->GetRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
				rotation = glm::rotate(rotation, transformable->GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
				rotation = glm::rotate(rotation, transformable->GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

				glm::mat4 trans;

				trans = rotation * scale;

				for (auto jt = vertexData.begin(); jt != vertexData.end(); jt++) {
					transVertDat.push_back(trans * glm::vec4(*jt, 1));
				}

				glm::vec3 min = glm::vec3(transVertDat[0].x, transVertDat[0].y, transVertDat[0].z);
				glm::vec3 max = glm::vec3(transVertDat[0].x, transVertDat[0].y, transVertDat[0].z);

				for (size_t i = 0; i < transVertDat.size(); i++) {
					if (transVertDat[i].x < min.x) { min.x = transVertDat[i].x; }
					if (transVertDat[i].y < min.y) { min.y = transVertDat[i].y; }
					if (transVertDat[i].z < min.z) { min.z = transVertDat[i].z; }
					if (transVertDat[i].x > max.x) { max.x = transVertDat[i].x; }
					if (transVertDat[i].y > max.y) { max.y = transVertDat[i].y; }
					if (transVertDat[i].z > max.z) { max.z = transVertDat[i].z; }
				}

				aabb->UpdateAABB(min, max);
			}
		}
	};
}

#endif
