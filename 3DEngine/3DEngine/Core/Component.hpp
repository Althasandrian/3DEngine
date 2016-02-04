#pragma once

namespace Engine {

	// Base Component
	class Component {
	public:
		Component() = default;
		virtual ~Component() = default;
		//virtual std::ofstream& Serialize(std::ofstream& os) = 0; //Onkohan t‰‰ virtual vai ei?
	};

	class Renderable : public Component {
	public:
		Renderable() = default;
		virtual ~Renderable() = default;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};

	class Transformable : public Component {
	public:
		Transformable() = default;
		virtual ~Transformable() = default;
		//std::ofstream& Serialize(std::ofstream& os) {}
	};
}