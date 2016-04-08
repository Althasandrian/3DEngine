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

		void CreateAABB(std::vector<glm::vec3> vertexData);
	private:
		std::vector<glm::vec3> _AABBVetrexData;
	};

	inline void AABB::Init() {}

	inline void AABB::Cleanup() {}

	inline void AABB::Update(DeltaTime deltaTime) {}

	inline void AABB::CreateAABB(std::vector<glm::vec3> vertexData) {
		//// min = minium coordinate of the box
		//// max = maxium coordinate of the box
		//Point min = V[0];
		//Point max = V[0];
		//for (i = 1; i < n; ++i)
		//{
		//	if (V[i].x < min.x) min.x = V[i].x;
		//	if (V[i].y < min.y) min.y = V[i].y;
		//	if (V[i].z < min.z) min.z = V[i].z;
		//	if (V[i].x > max.x) max.x = V[i].x;
		//	if (V[i].y > max.y) max.y = V[i].y;
		//	if (V[i].z > max.z) max.z = V[i].z;
		//}
	}
};

#endif