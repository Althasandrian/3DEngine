#ifndef Engine_Renderable_hpp
#define Engine_Renderable_hpp

#include <Core\Managers\EntityManager.hpp>

namespace Engine {

	class Renderable : public Component
	{
	public:
		Renderable(std::vector<float> data);
		virtual ~Renderable();

		void Init();
		void Cleanup();

		void Update(DeltaTime deltaTime);
		std::vector<float> GetVertexData();
	private:
		std::vector<float> _vertexData;
	};

	Renderable::Renderable(std::vector<float> data) { _vertexData = data; }

	Renderable::~Renderable() {}

	void Renderable::Init() {}

	void Renderable::Cleanup() {}

	void Renderable::Update(DeltaTime deltaTime) {}

	std::vector<float> Renderable::GetVertexData() { return _vertexData; }

};

#endif