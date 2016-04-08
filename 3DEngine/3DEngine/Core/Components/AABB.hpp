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

		void UpdateAABB();
	private:
		std::vector<glm::vec3> _AABBVetrexData;
	};

	inline void AABB::Init() {}

	inline void AABB::Cleanup() {}

	inline void AABB::Update(DeltaTime deltaTime) {}

	inline void AABB::UpdateAABB() {


		//glm::vec3 min = vertexData[0];
		//glm::vec3 max = vertexData[0];

		//for (size_t i = 0; i < vertexData.size(); i++) {
		//	if (vertexData[i].x < min.x) { min.x = vertexData[i].x; }
		//	if (vertexData[i].y < min.y) { min.y = vertexData[i].y; }
		//	if (vertexData[i].z < min.z) { min.z = vertexData[i].z; }
		//	if (vertexData[i].x < max.x) { max.x = vertexData[i].x; }
		//	if (vertexData[i].y < max.y) { max.y = vertexData[i].y; }
		//	if (vertexData[i].z < max.z) { max.z = vertexData[i].z; }
		//}
	}
};

#endif