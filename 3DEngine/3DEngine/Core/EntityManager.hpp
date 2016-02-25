#ifndef EntityManager_hpp
#define EntityManager_hpp

#include "Entity.hpp"
#include <vector>
#include <memory>

namespace Engine
{
	class EntityManager
	{
	public:
		static EntityManager* GetInstance() {
			static EntityManager instance;
			return &instance;
		};

		void AddEntity(std::shared_ptr<Entity> entity);
		template<typename T> std::vector<std::shared_ptr<T>> GetComponents();

	private:
		std::vector<std::shared_ptr<Entity>> _entities;

		EntityManager();
		~EntityManager();

		EntityManager(EntityManager const&);
		void operator=(EntityManager const&);
	};

	template<typename T> std::vector<std::shared_ptr<T>> EntityManager::GetComponents() {
		std::vector<std::shared_ptr<T>> temp;
		for each (std::shared_ptr<Entity> entity in _entities) {
			std::shared_ptr<T> tempPtr = entity->GetComponent<T>();
			if (tempPtr != nullptr) {
				temp.push_back(tempPtr);
			}
		}
		return temp;
	}
}

#endif