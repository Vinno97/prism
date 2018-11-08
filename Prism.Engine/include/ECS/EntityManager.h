#pragma once
#include <cstdio>
#include <vector>
#include <map>
#include <typeindex>
#include "Components/Component.h"
#include "Components/PositionComponent.h"
#include "Entity.h"

namespace ECS {

	using namespace Components;

	/// <summary>
	///	Handles the creation, management and removal of Entities.
	/// </summary>
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		///// <summary>
		///// Creates a new entity.
		///// </summary>
		///// <param name="fs">Components to be added to the new entity</param>
		///// <returns>The ID of the newly created entity.</returns>
		template <typename... Fs>
		int createEntity(Fs &&... fs) {
			return buildEntity(std::forward<Fs>(fs)...);
		}

		/// <summary>
		/// Adds a component to a given entity.
		/// </summary>
		/// <param name="entityId">The ID of the entity to add the component to.</param>
		/// <param name="entityId">The component to add to the entity.</param>
		template<class T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		void addComponentToEntity(unsigned int entityId, T& component)
		{
			const std::type_index type = std::type_index(typeid(component));

			if (entityComponents.find(type) != entityComponents.end()) {
				std::map<unsigned int, Component*> *components = &entityComponents.at(type);

				if (components->find(entityId) != components->end()) {
					throw std::runtime_error("Already attached a component of type " + *type.name() + *" to entity " + std::to_string(entityId));
				}
			}
			entityComponents[type][entityId] = new T(component);
		}

		/// <summary>
		/// Removes a component from a given entiy.
		/// </summary>
		/// <param name="entityId">The ID of the entity to remove the component from.</param>
		template<typename T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		void removeComponentFromEntity(unsigned int entityId) {
			const std::type_index type{ std::type_index(typeid(T)) };
			removeComponentFromEntity(entityId, type);
		}

		/// <summary>
		/// Retrieves a compnent from a given entity.
		/// </summary>
		/// <param name="entityId">The ID of the entity to get the component from.</param>
		/// <returns>A pointer to the component belonging to the entity.</returns>
		template<typename T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		T* getComponent(unsigned int entityId) const {
			const std::type_index type{ std::type_index(typeid(T)) };
			return static_cast<T*>(getComponent(entityId, type));

		}

		/// <summary>
		/// Returns whether or not an entity has a component.
		/// </summary>
		/// <param name="entityId">The ID of the entity to get the component from.</param>
		/// <returns>A boolean indicator whether the entity has the component.</returns>
		template<typename T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		bool hasComponent(unsigned int entityId) const {
			const std::type_index type{ std::type_index(typeid(T)) };
			return hasComponent(entityId, type);
		}

		/// <summary>
		/// Retrieves all entities with a certain component type.
		/// </summary>
		/// <returns>A vector containing combinations of entities and the matching component.</returns>
		template<typename T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		std::vector<Entity<T*>> getAllEntitiesWithComponent() const {
			auto const type = std::type_index(typeid(T));

			auto const entities = getAllEntitiesWithComponent(type);

			std::vector<Entity<T*>> result;

			result.reserve(entities.size());
			for (auto const& entry : entities) {
				Entity<T*> entity;
				entity.id = entry.id;
				entity.component = static_cast<T*>(entry.component);
				result.push_back(entity);
			}
			return result;
		}

		/// <summary>
		/// Removes an entity and its components.
		/// </summary>
		/// <param name="entityId">The ID of the entity to be removed.</param>
		void removeEntity(unsigned int entityId);

		EntityManager (const EntityManager &other); 


		/// <summary>
		/// Keeps a list of all instances of each component type.
		/// </summary>
		std::map<std::type_index, std::map<unsigned int, Component*>> entityComponents;
	private:
		unsigned int lastEntityId = 0;

		/// <summary>
		/// Keeps a list of all Listeners attached to the EntityManager.
		/// </summary>
		Component* getComponent(unsigned int entityId, std::type_index componentType) const;

		bool hasComponent(unsigned int entityId, std::type_index componentType) const;

		std::vector<Entity<Component*>> getAllEntitiesWithComponent(const std::type_index& componentType) const;

		void removeComponentFromEntity(unsigned int entityId, std::type_index componentType);

		template <typename F, typename... Fs>
		int buildEntity(F &&f) {
			addComponentToEntity(lastEntityId, f);
			return lastEntityId++;
		}

		template <typename F, typename... Fs>
		int buildEntity(F &&f, Fs &&... fs) {
			int entity = buildEntity(std::forward<Fs>(fs)...);
			addComponentToEntity(entity, f);
			return entity;
		}
	};
}