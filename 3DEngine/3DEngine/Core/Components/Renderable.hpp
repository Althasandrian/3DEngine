#ifndef Engine_Renderable_hpp
#define Engine_Renderable_hpp

#include <Core\Managers\EntityManager.hpp>

namespace Engine {

	class Renderable : public Component
	{
	public:
		Renderable();
		virtual ~Renderable();

		void Init();
		void Cleanup();

		void Update(DeltaTime deltaTime);
	private:
		float _vertexData;
	};

	Renderable::Renderable() {

	}

	Renderable::~Renderable() {

	}

	void Renderable::Init() {

	}

	void Renderable::Cleanup() {

	}

	void Renderable::Update(DeltaTime deltaTime) {

	}

};

#endif