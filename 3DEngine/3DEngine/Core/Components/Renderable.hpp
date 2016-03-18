#ifndef Engine_Renderable_hpp
#define Engine_Renderable_hpp

#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Renderable : public Component
	{
	public:
		Renderable(std::vector<GLfloat> vertexData, std::vector<GLuint> indiceData)
			: _vertexData(vertexData), _indiceData(indiceData) {};
		virtual ~Renderable();

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		std::vector<GLfloat> GetVertexData() { return _vertexData; };
		std::vector<GLuint> GetIndiceData() { return _indiceData; };
	private:
		std::vector<GLfloat> _vertexData;
		std::vector<GLuint> _indiceData;
	};

	void Renderable::Init() {}

	void Renderable::Cleanup() {}

	void Renderable::Update(DeltaTime deltaTime) {}

};

#endif