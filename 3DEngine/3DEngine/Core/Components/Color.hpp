#ifndef Engine_Color_hpp
#define Engine_Color_hpp

#include <Core/Managers/EntityManager.hpp>

namespace Engine {

	class Color : public Component
	{
	public:
		Color(std::vector<GLfloat> data) { _colorData = data; };
		virtual ~Color() {};

		virtual void Init() override;
		virtual void Cleanup() override;

		virtual void Update(DeltaTime deltaTime) override;

		std::vector<GLfloat> GetColorData() { return _colorData; };
	private:
		std::vector<GLfloat> _colorData;
	};

	void Color::Init() {}

	void Color::Cleanup() {}

	void Color::Update(DeltaTime deltaTime) {}

};

#endif