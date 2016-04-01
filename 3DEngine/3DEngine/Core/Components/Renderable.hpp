#ifndef Engine_Renderable_hpp
#define Engine_Renderable_hpp

#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Renderable : public Component
	{
	public:
		Renderable(std::vector<glm::fvec3> vertexData, std::vector<glm::uvec3> indiceData)
			: _vertexData(vertexData), _vertexIndexData(indiceData) {
			std::cout << "Renderable: Construct()" << std::endl;
		};
		virtual ~Renderable() { std::cout << "Renderable: Destruct()" << std::endl; };

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		std::vector<glm::fvec3> GetVertexData() { return _vertexData; };
		std::vector<glm::uvec3> GetIndiceData() { return _vertexIndexData; };
	private:
		std::vector<glm::fvec3> _vertexData;
		std::vector<glm::uvec3> _vertexIndexData;
	};

	void Renderable::Init() { std::cout << "Renderable: Init()" << std::endl; }

	void Renderable::Cleanup() { std::cout << "Renderable: Cleanup()" << std::endl; }

	void Renderable::Update(DeltaTime deltaTime) { std::cout << "Renderable: Update()" << std::endl; }

};

#endif