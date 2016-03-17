#ifndef Engine_Color_hpp
#define Engine_Color_hpp

#include <Core\Managers\EntityManager.hpp>

namespace Engine {

	class Color : public Component
	{
	public:
		Color(std::vector<float> data);
		virtual ~Color();

		void Init();
		void Cleanup();

		void Update(DeltaTime deltaTime);
		std::vector<float> GetColorData();
	private:
		std::vector<float> _colorData;
	};

	Color::Color(std::vector<float> data) { _colorData = data; }

	Color::~Color() {}

	void Color::Init() {}

	void Color::Cleanup() {}

	void Color::Update(DeltaTime deltaTime) {}

	std::vector<float> Color::GetColorData() { return _colorData; }

};

#endif