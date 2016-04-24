#ifndef Engine_AABB_hpp
#define Engine_AABB_hpp

#include <glm/glm.hpp>
#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class AABB : public Component
	{
	public:
		AABB() {};
		virtual ~AABB() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		void UpdateAABB(glm::vec3 min, glm::vec3 max);

		std::vector<glm::vec3> GetVertexData() { return _AABBVetrexData; };
		std::vector<glm::uvec3> GetIndiceData() { return _AABBIndiceData; };

		glm::mat4 GetTransform() { return transform; }
	private:
		std::vector<glm::vec3> _AABBVetrexData;
		std::vector<glm::uvec3> _AABBIndiceData;

		glm::vec3 size;
		glm::vec3 center;
		glm::mat4 transform;
	};

	inline void AABB::Init() {
		_AABBIndiceData.push_back(glm::uvec3(0, 1, 2));
		_AABBIndiceData.push_back(glm::uvec3(2, 3, 0));
		_AABBIndiceData.push_back(glm::uvec3(1, 5, 6));
		_AABBIndiceData.push_back(glm::uvec3(6, 2, 1));
		_AABBIndiceData.push_back(glm::uvec3(7, 6, 5));
		_AABBIndiceData.push_back(glm::uvec3(5, 4, 7));
		_AABBIndiceData.push_back(glm::uvec3(4, 0, 3));
		_AABBIndiceData.push_back(glm::uvec3(3, 7, 4));
		_AABBIndiceData.push_back(glm::uvec3(4, 5, 1));
		_AABBIndiceData.push_back(glm::uvec3(1, 0, 4));
		_AABBIndiceData.push_back(glm::uvec3(3, 2, 6));
		_AABBIndiceData.push_back(glm::uvec3(6, 7, 3));
	}

	inline void AABB::Cleanup() {}

	inline void AABB::Update(DeltaTime deltaTime) {}

	inline void AABB::UpdateAABB(glm::vec3 min, glm::vec3 max) {
		_AABBVetrexData.clear();

		_AABBVetrexData.push_back(glm::vec3(min.x, min.y, max.z));
		_AABBVetrexData.push_back(glm::vec3(max.x, min.y, max.z));
		_AABBVetrexData.push_back(glm::vec3(max.x, max.y, max.z));
		_AABBVetrexData.push_back(glm::vec3(min.x, max.y, max.z));
		_AABBVetrexData.push_back(glm::vec3(min.x, min.y, min.z));
		_AABBVetrexData.push_back(glm::vec3(max.x, min.y, min.z));
		_AABBVetrexData.push_back(glm::vec3(max.x, max.y, min.z));
		_AABBVetrexData.push_back(glm::vec3(min.x, max.y, min.z));

		glm::vec3 size = glm::vec3(max.x - min.x, max.y - min.y, max.z - min.z);
		glm::vec3 center = glm::vec3((min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2);
		transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);
	}
};

#endif