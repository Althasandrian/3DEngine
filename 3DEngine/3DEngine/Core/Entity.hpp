#ifndef Entity_h
#define Entity_h

#include <iostream>
#include <typeindex>
#include <memory>
#include <map>

namespace Engine {
	class Component;

	class Entity
	{
	public:
		Entity();
		~Entity();

		// Component //
		template<typename T> void AddComponent(std::shared_ptr<T> component);
		template<typename T> std::shared_ptr<T> GetComponent();
		template<typename T> void RemoveComponent();

	private:
		std::map<const std::type_info*, std::shared_ptr<Component>> _components;
	};

	inline Entity::Entity() {}

	inline Entity::~Entity() {

	}

	template<typename T> void Entity::AddComponent(std::shared_ptr<T> component) {
		_components[&typeid(*component)] = component;
	}

	template<typename T> std::shared_ptr<T> Entity::GetComponent() {
		if (_components.count(&typeid(T)) != 0) {
			return std::static_pointer_cast<T>(_components[&typeid(T)]);
		}
		return nullptr;
	}

	template<typename T> void Entity::RemoveComponent() {
		if (_components.count(&typeid(T)) != 0) {
			auto it = _components.find(typeid(T));
			delete it->second;
			_components.erase(it);
		}
	}
}
#endif