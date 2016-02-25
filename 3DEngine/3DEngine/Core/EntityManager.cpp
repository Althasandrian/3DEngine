#include "EntityManager.hpp"

namespace Engine
{
	EntityManager::EntityManager() {

	}

	EntityManager::~EntityManager() {

	}

	void EntityManager::AddEntity(std::shared_ptr<Entity> entity) {
		_entities.push_back(entity);
	}
}