#pragma once

#include <cstdio>
#include <vector>
#include <map>
#include <typeindex>


#include "Components/Component.h"
#include "Components/PositionComponent.h"

#include "Listener.h"
#include "EntityWithComponent.h"

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

		template<class A>
		int createEntity(A& c1) {
			entities.push_back(++lastEntityId);
			addComponentToEntity(lastEntityId, c1);
			return lastEntityId;
		}

		template<class A, class B>
		int createEntity(A& c1, B& c2) {
			int entity = createEntity(c1);
			addComponentToEntity(entity, c2);
			return entity;
		}

		template<class A, class B, class C>
		int createEntity(A& c1, B& c2, C& c3) {
			int entity = createEntity(c1, 2c);
			addComponentToEntity(entity, c3);
			return entity;
		}

		template<class A, class B, class C, class D>
		int createEntity(A& c1, B& c2, C& c3, D& c4) {
			int entity = createEntity(c1, 2c, c3);
			addComponentToEntity(entity, c4);
			return entity;
		}

		template<class A, class B, class C, class D, class E>
		int createEntity(A& c1, B& c2, C& c3, D& c4, E& c5) {
			int entity = createEntity(c1, 2c, c3, c4);
			addComponentToEntity(entity, c5);
			return entity;
		}

		template<class A, class B, class C, class D, class E, class F, class G>
		int createEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7) {
			int entity = createEntity(c1, 2c, c3, c4, c5, c6);
			addComponentToEntity(entity, c7);
			return entity;
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H>
		int createEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8) {
			int entity = createEntity(c1, 2c, c3, c4, c5, c6, c7);
			addComponentToEntity(entity, c8);
			return entity;
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I>
		int createEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9) {
			int entity = createEntity(c1, 2c, c3, c4, c5, c6, c7, c8);
			addComponentToEntity(entity, c9);
			return entity;
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I, class J>
		int createEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9, J& c10) {
			int entity = createEntity(c1, 2c, c3, c4, c5, c6, c7, c8, c9);
			addComponentToEntity(entity, c10);
			return entity;
		}


		template<class T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		void addComponentToEntity(unsigned int entityId, T& component)
		{
			const std::type_index type = std::type_index(typeid(component));

			if (entityComponents.find(type) == entityComponents.end()) {
				std::map<unsigned int, Component*> *components = &entityComponents[type];

				if (components->find(entityId) != components->end()) {
					throw std::runtime_error("Already attached a component of type " + *type.name() + *" to entity " + std::to_string(entityId));
				}
			}
			entityComponents[type][entityId] = new T(component);
		}

		template<typename T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		void removeComponentFromEntity(unsigned int entityId) {
			const std::type_index type{ std::type_index(typeid(T)) };
			removeComponentFromEntity(entityId, type);
		}

		template<typename T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		T* getComponent(unsigned int entityId) const {
			const std::type_index type{ std::type_index(typeid(T)) };
			return static_cast<T*>(getComponent(entityId, type));

		}

		template<typename T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
		std::vector<EntityWithComponent<T>> getAllEntities() const {
			auto const type = std::type_index(typeid(T));

			auto const test = entities[type];

			std::vector<EntityWithComponent<T>> result;

			result.reserve(test.size());
			for (auto const& pair : test) {
				EntityWithComponent<T> test;
				test.id = pair.first;
				test.component;

				result.push_back(test);
			}

			return result;
		}

		void removeEntity(unsigned int entityId);

	private:
		unsigned int lastEntityId = 0;


		/// <summary>
		/// Keeps a list of all instances of each component type.
		/// </summary>
		//std::map<unsigned int, std::map<std::type_index, Component>> entityComponents;
		std::map<std::type_index, std::map<unsigned int, Component*>> entityComponents;

		/// <summary>
		/// Keeps a list of all entities Entity.
		/// </summary>
		std::vector<unsigned int> entities;

		/// <summary>
		/// Keeps a list of all Listeners attached to the EntityManager.
		/// </summary>

		Component* getComponent(unsigned int entityId, std::type_index componentType) const;


		void removeComponentFromEntity(unsigned int entityId, std::type_index componentType);
	};
}