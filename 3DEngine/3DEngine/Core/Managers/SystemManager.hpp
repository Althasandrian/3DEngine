#ifndef Engine_SystemManager_hpp
#define Engine_SystemManager_hpp

//--------------------------------------------------------------------------------------//
// SystemManager.hpp																	//
// [3/10/2016 Rasmus]																	//
//--------------------------------------------------------------------------------------//
																						//
#include <vector>																		//
#include <memory>																		//
																						//
#include <Core\Time.hpp>																//
																						//
namespace Engine																		//
{																						//
	//--------------------------------------------------------------------------//		//
	// STRUCT - System															//		//
	//--------------------------------------------------------------------------//		//
	struct System																//		//
	{																			//		//
		System() : _paused(false) {};											//		//
		virtual ~System() {};													//		//
																				//		//
		virtual void Init() = 0;												//		//
		virtual void Cleanup() = 0;												//		//
																				//		//
		virtual void Pause() = 0;												//		//
		virtual void Resume() = 0;												//		//
																				//		//
		virtual void Update(DeltaTime deltaTime) = 0;							//		//
																				//		//
	protected:																	//		//
		bool _paused;															//		//
	};																			//		//
	//--------------------------------------------------------------------------//		//
																						//
	//--------------------------------------------------------------------------//		//
	// CLASS - SystemManager													//		//
	//--------------------------------------------------------------------------//		//
	class SystemManager															//		//
	{																			//		//
	public:																		//		//
		static SystemManager* GetInstance() {									//		//
			static SystemManager SysMan;										//		//
			return &SysMan;														//		//
		};																		//		//
																				//		//
		template <typename T, typename ...args> void AddSystem(args&&... param);//		//
		template <typename T> void RemoveSystem();								//		//
		template <typename T> void PauseSystem();								//		//
		template <typename T> void ResumeSystem();								//		//
																				//		//
		void Update(DeltaTime deltaTime);										//		//
		void Clear();															//		//
																				//		//
	private:																	//		//
		std::vector<std::shared_ptr<System>> _systems;							//		//
																				//		//
		SystemManager() {};														//		//
		~SystemManager() { Clear(); };											//		//
																				//		//
		SystemManager(SystemManager const&);									//		//
		void operator=(SystemManager const&);									//		//
	};																			//		//
	//--------------------------------------------------------------------------//		//
																						//
	//--------------------------------------------------------------------------//		//
	// DEFINITIONS - SystemManager												//		//
	//--------------------------------------------------------------------------//		//
	template <typename T, typename ...args> void SystemManager::AddSystem(args&&... param) {
		for (auto it : _systems) {												//		//
			if (std::dynamic_pointer_cast<T>(it) != nullptr) { return; }		//		//
		}																		//		//
		_systems.push_back(std::make_shared<T>(param...));						//		//
		_systems.back()->Init();												//		//
	}																			//		//
																				//		//
	template <typename T> void SystemManager::RemoveSystem() {					//		//
		for (auto it = _systems.begin(); it != _systems.end();) {				//		//
			if (std::dynamic_pointer_cast<T>(*it) != nullptr) {					//		//
				it->get()->Cleanup();											//		//
				it = _systems.erase(it);										//		//
			}																	//		//
			else {																//		//
				it++;															//		//
			}																	//		//
		}																		//		//
	}																			//		//
																				//		//
	template <typename T> void SystemManager::PauseSystem() {					//		//
		for (auto it : _systems) {												//		//
			if (std::dynamic_pointer_cast<T>(it) != nullptr) {					//		//
				it->Pause();													//		//
			}																	//		//
		}																		//		//
	}																			//		//
																				//		//
	template <typename T> void SystemManager::ResumeSystem() {					//		//
		for (auto it : _systems) {												//		//
			if (std::dynamic_pointer_cast<T>(it) != nullptr) {					//		//
				it->Resume();													//		//
			}																	//		//
		}																		//		//
	}																			//		//
																				//		//
	inline void SystemManager::Clear() {										//		//
		while (!_systems.empty()) {												//		//
			_systems.back()->Cleanup();											//		//
			_systems.pop_back();												//		//
		}																		//		//
	}																			//		//
																				//		//
	inline void SystemManager::Update(DeltaTime deltaTime) {					//		//
		for (auto it : _systems) {												//		//
			it->Update(deltaTime);												//		//
		}																		//		//
	}																			//		//
	//--------------------------------------------------------------------------//		//
																						//
}																						//
																						//
//--------------------------------------------------------------------------------------//

#endif