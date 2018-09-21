#include "ECS/EntityManager.h"

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <string>
#include <initializer_list>

#include "ECS/Components/PositionComponent.h"

namespace ECS {
	using namespace Components;

	EntityManager::EntityManager()
		= default;


	EntityManager::~EntityManager()
		= default;


	Component* EntityManager::getComponent(unsigned int entityId, std::type_index componentType) const
	{
		try {
			return entityComponents.at(componentType).at(entityId);
		}
		catch (const std::out_of_range& exception) {
			throw std::runtime_error(std::string("No component of type ") + componentType.name() + " found for entity " + std::to_string(entityId));
		}
	}

	void EntityManager::removeComponentFromEntity(unsigned int entityId, std::type_index componentType)
	{
		entityComponents.at(componentType).erase(entityId);
		if (entityComponents.at(componentType).empty()) {
			entityComponents.erase(componentType);
		}
	}

	void EntityManager::removeEntity(unsigned int entityId) {
		std::map<std::type_index, std::map<unsigned int, Component*>>::iterator itr = entityComponents.begin();
		while (itr != entityComponents.end()) {
			itr->second.erase(entityId);

			if (itr->second.empty()) {
				itr = entityComponents.erase(itr);
			}
			else {
				++itr;
			}
		}
	}


}