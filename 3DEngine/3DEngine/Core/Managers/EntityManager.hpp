#ifndef Engine_EntityManager_hpp
#define Engine_EntityManager_hpp

//--------------------------------------------------------------------------------------------------------------------------//
// EntityManager.hpp																										//
// [3/14/2016 Rasmus]																										//
//--------------------------------------------------------------------------------------------------------------------------//
																															//
#include <unordered_map>																									//
#include <string>																											//
#include <memory>																											//
																															//
#include <Core\Time.hpp>																									//
																															//
namespace Engine																											//
{																															//
	//--------------------------------------------------------------------------------------------------------------//		//
	// STRUCT - Component																							//		//
	//--------------------------------------------------------------------------------------------------------------//		//
	struct Component																								//		//
	{																												//		//
		Component() {};																								//		//
		virtual ~Component() {};																					//		//
																													//		//
		virtual void Init() = 0;																					//		//
		virtual void Cleanup() = 0;																					//		//
																													//		//
		virtual void Update(DeltaTime deltaTime) = 0;																//		//
	};																												//		//
	//--------------------------------------------------------------------------------------------------------------//		//
																															//
	//--------------------------------------------------------------------------------------------------------------//		//
	// STRUCT - Entity																								//		//
	//--------------------------------------------------------------------------------------------------------------//		//
	struct Entity																									//		//
	{																												//		//
		Entity() {};																								//		//
		virtual ~Entity() {};																						//		//
																													//		//
		virtual void Init() = 0;																					//		//
		virtual void Cleanup() = 0;																					//		//
																													//		//
		virtual void Update(DeltaTime deltaTime) = 0;																//		//
																													//		//
		template <typename T> void AddComponent();																	//		//
		template <typename T> void RemoveComponent();																//		//
																													//		//
		template <typename T> std::shared_ptr<Component> GetComponent();											//		//
		std::vector<std::shared_ptr<Component>> GetComponents();													//		//
																													//		//
	protected:																										//		//
		std::vector<std::shared_ptr<Component>> _components;														//		//
	};																												//		//
	//--------------------------------------------------------------------------------------------------------------//		//
																															//
	//--------------------------------------------------------------------------------------------------------------//		//
	// DEFINITIONS - Entity																							//		//
	//--------------------------------------------------------------------------------------------------------------//		//
	template <typename T> void Entity::AddComponent() {																//		//
		for (auto it : _components) {																				//		//
			if (std::dynamic_pointer_cast<T>(it) != nullptr) { return; }											//		//
		}																											//		//
		_components.push_back(std::make_shared<T>());																//		//
		_components.back()->Init();																					//		//
	}																												//		//
																													//		//
	template <typename T> void Entity::RemoveComponent() {															//		//
		for (auto it = _components.begin(); it != _components.end();) {												//		//
			if (std::dynamic_pointer_cast<T>(*it) != nullptr) {														//		//
				it->get()->Cleanup();																				//		//
				it = _components.erase(it);																			//		//
			}																										//		//
			else {																									//		//
				it++;																								//		//
			}																										//		//
		}																											//		//
	}																												//		//
																													//		//
	template <typename T> std::shared_ptr<Component> Entity::GetComponent() {										//		//
		for (auto it : _components) {																				//		//
			if (std::dynamic_pointer_cast<T>(it) != nullptr) {														//		//
				return it;																							//		//
			}																										//		//
		}																											//		//
		return nullptr;																								//		//
	}																												//		//
																													//		//
	std::vector<std::shared_ptr<Component>> Entity::GetComponents() {												//		//
		return _components;																							//		//
	}																												//		//
	//--------------------------------------------------------------------------------------------------------------//		//
																															//
	//--------------------------------------------------------------------------------------------------------------//		//
	// CLASS - EntityManager																						//		//
	//--------------------------------------------------------------------------------------------------------------//		//
	class EntityManager
	{
	public:
		static EntityManager* GetInstance() {
			static EntityManager EnMan;
			return &EnMan;
		}

		void AddEntity(std::string name, std::shared_ptr<Entity> entity);
		void RemoveEntity(std::string name);

		void Update(DeltaTime deltaTime);

		void Clear();

		std::shared_ptr<Entity> GetEntity(std::string name);

		template <typename T> void AddComponent(std::string name);

		template <typename T> std::vector<std::shared_ptr<Component>> GetComponents();
		template <typename T> std::vector<std::shared_ptr<Component>> GetComponents(std::string name);

		std::vector<std::shared_ptr<Component>> GetComponents();
		std::vector<std::shared_ptr<Component>> GetComponents(std::string name);
	private:
		std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;

		EntityManager() {};
		~EntityManager() { Clear(); };

		EntityManager(EntityManager const&);
		void operator=(EntityManager const&);
	};

	//--------------------------------------------------------------------------------------------------------------//		//
	// DEFINITIONS - EntityManager																					//		//
	//--------------------------------------------------------------------------------------------------------------//		//
	inline void EntityManager::AddEntity(std::string name, std::shared_ptr<Entity> entity) {
		_entities.insert(std::make_pair(name, entity));
		entity->Init();
	}

	inline void EntityManager::RemoveEntity(std::string name) {
		_entities.find(name)->second->Cleanup();
		_entities.erase(name);
	}

	inline void EntityManager::Update(DeltaTime deltaTime) {
		for (auto it : _entities) {
			it.second->Update(deltaTime);
		}
	}

	inline void EntityManager::Clear() {
		while (!_entities.empty()) {
			_entities.begin()->second->Cleanup();
			_entities.erase(_entities.begin());
		}
	}

	inline std::shared_ptr<Entity> EntityManager::GetEntity(std::string name) {
		return _entities.find(name)->second;
	}

	template <typename T> void EntityManager::AddComponent(std::string name) {
		GetEntity(name)->AddComponent<T>();
	}

	template <typename T> std::vector<std::shared_ptr<Component>> EntityManager::GetComponents() {
		std::vector <std::shared_ptr<Component>> tempCompVec;
		for (auto it : _entities) {
			tempCompVec.push_back(it.second->GetComponent<T>());
		}
		return tempCompVec;
	}

	template <typename T> std::vector<std::shared_ptr<Component>> EntityManager::GetComponents(std::string name) {
		std::vector <std::shared_ptr<Component>> tempCompVec;
		tempCompVec.push_back(_entities.find(name)->second->GetComponent<T>());
		return tempCompVec;
	}

	inline std::vector<std::shared_ptr<Component>> EntityManager::GetComponents() {
		std::vector <std::shared_ptr<Component>> tempCompVec;
		for (auto it : _entities) {
			std::vector<std::shared_ptr<Component>> temp = it.second->GetComponents();
			tempCompVec.insert(tempCompVec.end(), temp.begin(), temp.end());
		}
		return tempCompVec;
	}

	inline std::vector<std::shared_ptr<Component>> EntityManager::GetComponents(std::string name) {
		std::vector <std::shared_ptr<Component>> tempCompVec;
		std::vector<std::shared_ptr<Component>> temp = _entities.find(name)->second->GetComponents();
		tempCompVec.insert(tempCompVec.end(), temp.begin(), temp.end());
		return tempCompVec;
	}
}

#endif