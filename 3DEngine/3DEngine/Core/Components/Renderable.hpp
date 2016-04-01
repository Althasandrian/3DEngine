#ifndef Engine_Renderable_hpp
#define Engine_Renderable_hpp

#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Renderable : public Component
	{
	public:
		Renderable(std::vector<glm::vec3> vertexData, std::vector<glm::vec3> indiceData)
			: _vertexData(vertexData), _indiceData(indiceData) {};
		virtual ~Renderable() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		std::vector<glm::vec3> GetVertexData() { return _vertexData; };
		std::vector<glm::vec3> GetIndiceData() { return _indiceData; };
	private:
		std::vector<glm::vec3> _vertexData;
		std::vector<glm::vec3> _indiceData;
	};

	void Renderable::Init() {}

	void Renderable::Cleanup() {}

	void Renderable::Update(DeltaTime deltaTime) {}

};

#endif