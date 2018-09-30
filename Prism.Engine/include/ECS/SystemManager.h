#pragma once

#include "ECS/System.h"
namespace ECS {

	/// <summary>
	/// Handles the registration, unregistration and retrieval of systems. 
	/// </summary>
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		/// <summary>
		/// Unregisters a system.
		/// </summary>
		/// <param name"system">The system that needs to be unregisterd </param>
		template<typename T, typename = std::enable_if < std::is_base_of<System, T>::value>>
		void unRegisterSystem(T& system) {

			const std::type_index type = std::type_index(typeid(system));

			unRegisterSystem(type);
		}

		/// <summary>
		/// Returns the requested system.
		/// </summary>
		template<typename T, typename = std::enable_if < std::is_base_of<System, T>::value>>
		T* getSystem() const
		{
			const std::type_index type{ std::type_index(typeid(T)) };
			return static_cast<T*>(getSystem(type));
		}

		/// <summary>
		/// Registers a system and ensures that there is only one instance of it.
		/// </summary>
		/// <param name"system">The system that needs to be registerd </param>
		template<typename A, typename B, typename = std::enable_if < std::is_base_of<System, A>::value>>
		void registerSystem(B& system) {

			const std::type_index type = std::type_index(typeid(system));

			if (systems.find(type) != systems.end()) {
				throw std::runtime_error("There can only one type of " + *type.name() + *" registered");
			}
			systems[type] = new B(system);
		}

		/// <summary>
		/// Registers a system and ensures that there is only one instance of it.
		/// </summary>
		/// <param name"system">The system that needs to be registerd </param>
		template<class A>
		void registerSystem(A& system) {
			registerSystem<A,A>(system);
		}


	private:
		/// <summary>
		/// A dictonary with all the registered systems.
		/// </summary>
		std::map<std::type_index, System*> systems;


		void unRegisterSystem(std::type_index systemType);
		void registerSystem(std::type_index systemType, System* system);
		System* getSystem(std::type_index systemType) const;
	};
}
