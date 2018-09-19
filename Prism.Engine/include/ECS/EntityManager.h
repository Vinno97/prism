#pragma once

#include <cstdio>
#include <vector>
#include <map>

#include "Component.h"
#include "Listener.h"

typedef void *EntityHandle;

namespace ECS {

	/// <summary>
	///	Handles the creation, management and removal of Entities.
	/// </summary>
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		/// <summary>
		/// Creates a new Entity with one or more predefined Components.
		/// </summary>
		template<class A>
		EntityHandle makeEntity(A& c1)
		{
			Component* components[] = { &c1 };
			unsigned int componentIDs[] = { A::ID };
			return makeEntity(components, componentIDs, 1);
		}

		template<class A, class B>
		EntityHandle makeEntity(A& c1, B& c2)
		{
			Component* components[] = { &c1, &c2 };
			unsigned int componentIDs[] = { A::ID, B::ID };
			return makeEntity(components, componentIDs, 2);
		}

		template<class A, class B, class C>
		EntityHandle makeEntity(A& c1, B& c2, C& c3)
		{
			Component* components[] = { &c1, &c2, &c3 };
			unsigned int componentIDs[] = { A::ID, B::ID, C::ID };
			return makeEntity(components, componentIDs, 3);
		}

		template<class A, class B, class C, class D>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4)
		{
			Component* components[] = { &c1, &c2, &c3, &c4 };
			unsigned int componentIDs[] = { A::ID, B::ID, C::ID, D::ID };
			return makeEntity(components, componentIDs, 4);
		}

		template<class A, class B, class C, class D, class E>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5)
		{
			Component* components[] = { &c1, &c2, &c3, &c4, &c5 };
			unsigned int componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID };
			return makeEntity(components, componentIDs, 5);
		}

		template<class A, class B, class C, class D, class E, class F>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6)
		{
			Component* components[] = { &c1, &c2, &c3, &c4, &c5, &c6 };
			unsigned int componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID };
			return makeEntity(components, componentIDs, 6);
		}

		template<class A, class B, class C, class D, class E, class F, class G>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7)
		{
			Component* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7 };
			unsigned int componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID };
			return makeEntity(components, componentIDs, 7);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8)
		{
			Component* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8 };
			unsigned int componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID };
			return makeEntity(components, componentIDs, 8);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9)
		{
			Component* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9 };
			unsigned int componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID };
			return makeEntity(components, componentIDs, 9);
		}

		template<class A, class B, class C, class D, class E, class F, class G, class H, class I, class J>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9, J& c10)
		{
			Component* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10 };
			unsigned int componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID, J::ID };
			return makeEntity(components, componentIDs, 10);
		}


		/// <summary>
		/// Adds a Component to an Entity.
		/// </summary>
		template<class Component>
		inline void addComponent(EntityHandle entity, Component* component)
		{
			addComponentInternal(entity, handleToEntity(entity), Component::ID, component);
			for (unsigned int i = 0; i < listeners.size(); i++) {
				const std::vector<unsigned int>& componentIDs = listeners[i]->getComponentIDs();
				if (listeners[i]->shouldNotifyOnAllComponentOperations()) {
					listeners[i]->onAddComponent(entity, Component::ID);
				}
				else {
					for (unsigned int j = 0; j < componentIDs.size(); j++) {
						if (componentIDs[j] == Component::ID) {
							listeners[i]->onAddComponent(entity, Component::ID);
							break;
						}
					}
				}
			}
		}

		/// <summary>
		/// Removes a Component of a certain type from an Entity.
		/// </summary>
		template<class Component>
		bool removeComponent(EntityHandle entity)
		{
			for (unsigned int i = 0; i < listeners.size(); i++) {
				const std::vector<unsigned int>& componentIDs = listeners[i]->getComponentIDs();
				for (unsigned int j = 0; j < componentIDs.size(); j++) {
					if (listeners[i]->shouldNotifyOnAllComponentOperations()) {
						listeners[i]->onRemoveComponent(entity, Component::ID);
					}
					else {
						if (componentIDs[j] == Component::ID) {
							listeners[i]->onRemoveComponent(entity, Component::ID);
							break;
						}
					}
				}
			}
			return removeComponentInternal(entity, Component::ID);
		}
	private:
		/// <summary>
		/// Keeps a list of all instances of each compoent type.
		/// </summary>
		std::map<unsigned int, std::vector<unsigned short>> components;

		/// <summary>
		/// Keeps a list of all component on an Entity.
		/// </summary>
		std::vector<std::pair<unsigned int, std::vector<std::pair<unsigned int, unsigned int> > >* > entities;

		/// <summary>
		/// Keeps a list of all Listeners attached to the EntityManager.
		/// </summary>
		std::vector<Listener*> listeners;

		inline std::pair<unsigned int, std::vector<std::pair<unsigned int, unsigned int> > >* handleToRawType(EntityHandle handle)
		{
			return (std::pair<unsigned int, std::vector<std::pair<unsigned int, unsigned int> > >*)handle;
		}

		inline unsigned int handleToEntityIndex(EntityHandle handle)
		{
			return handleToRawType(handle)->first;
		}

		inline std::vector<std::pair<unsigned int, unsigned int> >& handleToEntity(EntityHandle handle)
		{
			return handleToRawType(handle)->second;
		}


		bool removeComponentInternal(EntityHandle handle, unsigned int componentID);
		void addComponentInternal(EntityHandle handle, std::vector<std::pair<unsigned int, unsigned int> >& entity, unsigned int componentID, BaseComponent* component);
	};
}