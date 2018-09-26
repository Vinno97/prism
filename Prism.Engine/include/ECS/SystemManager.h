#pragma once

#include "ECS/System.h"
namespace ECS {
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		template<typename T, typename = std::enable_if < std::is_base_of<System, T>::value>>
		void unRegisterSystem(std::type_index systemType) {
			unRegisterSystem(systemType);
		}

		template<typename T, typename = std::enable_if < std::is_base_of<System, T>::value>>
		T* getSystem(std::type_index systemType) const
		{
			const std::type_index type{ std::type_index(typeid(T)) };
			return static_cast<T*>(getSystem(systemType, type));
		}

		template<class A, class B>
		void registerSystem(B& system) {

			const std::type_index type = std::type_index(typeid(system));

			if (systems.find(type) != systems.end()) {
				throw std::runtime_error("There can only one type of " + *type.name() + *" registered");
			}
			systems[type] = new B(system);
		}

		template<class A>
		void registerSystem(A& system) {
			registerSystem<A>(system);

		}


	private:
		std::map<std::type_index, System*> systems;
		void unRegisterSystem(std::type_index systemType);
		void registerSystem(std::type_index systemType, System* system);
		System* getSystem(std::type_index systemType) const;
	};
}
