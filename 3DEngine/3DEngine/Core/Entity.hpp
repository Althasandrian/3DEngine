#ifndef Entity_h
#define Entity_h

#include <iostream>
#include "EntityManager.hpp"
#include <typeindex>
#include <memory>
#include <map>


class Component;

class Entity
{
public:
	Entity();
	~Entity();

	unsigned GetID() { return _uniqueID; }

	template<typename T>
	void AddComponent(T* component);

	template<typename T>
	T* GetComponent();

	template<typename T>
	void RemoveComponent();
private:
	unsigned _uniqueID;
	std::map<std::type_index, Component*> _components;
};

Entity::Entity() {
	_uniqueID = Engine::EntityManager::GetID();
}

Entity::~Entity() {

}

template<typename T>
void Entity::AddComponent(T* component) {
	_components[std::type_index(typeid(*component))] = component;
}

template<typename T>
T* Entity::GetComponent() {
	std::type_index index(typeid(T));
	if (_components.count(std::type_index(typeid(T))) != 0) {
		return static_cast<T*>(_components[index]);
	}
	else {
		return nullptr;
	}
}

template<typename T>
void Entity::RemoveComponent() {
	std::type_index index(typeid(T));
	if (_components.count(std::type_index(typeid(T))) != 0) {
		auto it = _components.find(std::type_index(typeid(T)));
		delete it->second;
		_components.erase(it);
	}
}

#endif