#pragma once

#include "ECS/Systems/System.h"

namespace ECS {
	using namespace ECS::Systems;

	/// <summary>
	/// Handles the registration, unregistration and retrieval of systems.
	/// </summary>
	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		/// <summary>
		/// Unregisters a System of a certain type.
		/// </summary>
		/// <param name"system">The system that needs to be unregisterd </param>
		template<typename T, typename = std::enable_if_t < std::is_base_of<System, T>::type::value>>
		void unRegisterSystem(T& system) {

			const std::type_index type = std::type_index(typeid(system));

			unRegisterSystem(type);
		}

		/// <summary>
		/// Returns a System of the requested type.
		/// </summary>
		/// <returns>A pointer to the requested system.</returns>
		template<typename T, typename = std::enable_if_t < std::is_base_of<System, T>::type::value>>
		T* getSystem() const
		{
			const std::type_index type{ std::type_index(typeid(T)) };
			return static_cast<T*>(getSystem(type));
		}
		/// <summary>
		/// Gets all systems by priority.
		/// </summary>
		/// <returns></returns>
		 std::map<int, std::map<std::type_index, std::unique_ptr<System>>>& getAllSystems();


		/// <summary>
		/// Registers a System and ensures that there is only one instance of it.
		/// </summary>
		/// <param name"system">The system that needs to be registerd </param>
		//template<typename A, typename B, typename = std::enable_if_t < std::is_base_of<System, A>::type::value>>
		template <int P, typename A, typename B, typename... Fs>
		SystemManager &registerSystem(Fs &&... fs) {

			const std::type_index type = std::type_index(typeid(A));
			for (auto& systems : prioritizedSystems) {
				if (systems.second.find(type) != systems.second.end()) {
					throw std::runtime_error("There can only one type of " + *type.name() + *" registered");
				}
			}
			prioritizedSystems[P][type] = std::move(std::make_unique<B>(std::forward<Fs>(fs)...));
			return *this;
		}

		/// <summary>
		/// Registers a System and ensures that there is only one instance of it.
		/// </summary>
		/// <param name"system">The system that needs to be registerd </param>
		template<int P, class A, typename... Fs>
		SystemManager &registerSystem(Fs &&... fs) {
			return registerSystem<P, A, A>(std::forward<Fs>(fs)...);
		}


	private:
		/// <summary>
		/// A dictonary with all the registered systems.
		/// </summary>
		//std::map<std::type_index, System*> systems;
		std::map<int, std::map<std::type_index, std::unique_ptr<System>>> prioritizedSystems;

		void unRegisterSystem(std::type_index systemType);
		System* getSystem(std::type_index systemType) const;
	};
}
