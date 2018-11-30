#include "ECS/EntityManager.h"
#include <iostream>
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

	EntityManager & EntityManager::operator=(const EntityManager & other)
	{
		if (this != &other) {
			lastEntityId = other.lastEntityId;

			for (auto it = other.entityComponents.begin(); it != other.entityComponents.end(); it++)
			{
				std::unordered_map<unsigned int, Component*> newMap;
				for (auto itSub = it->second.begin(); itSub != it->second.end(); itSub++)
				{
					newMap[itSub->first] = itSub->second->Clone();
				}
				entityComponents[it->first] = newMap;

				this->entityComponents.insert(other.entityComponents.begin(), other.entityComponents.end());
			}
		}
		return *this;
	}

	EntityManager::EntityManager(EntityManager && other)
	{
		for (auto it = other.entityComponents.begin(); it != other.entityComponents.end(); it++)
		{
			std::unordered_map<unsigned int, Component*> newMap;
			for (auto itSub = it->second.begin(); itSub != it->second.end(); itSub++)
			{
				newMap[itSub->first] = itSub->second->Clone();
			}
			this->entityComponents[it->first] = newMap;

			this->entityComponents.insert(other.entityComponents.begin(), other.entityComponents.end());
		}

		this->lastEntityId = other.lastEntityId;
		other.entityComponents.clear();
		other.lastEntityId = 0;
	}

	EntityManager & EntityManager::operator=(EntityManager && other)
	{
		if (this != &other) {
			for (auto it = other.entityComponents.begin(); it != other.entityComponents.end(); it++)
			{
				std::unordered_map<unsigned int, Component*> newMap;
				for (auto itSub = it->second.begin(); itSub != it->second.end(); itSub++)
				{
					newMap[itSub->first] = itSub->second->Clone();
				}
				this->entityComponents[it->first] = newMap;

				this->entityComponents.insert(other.entityComponents.begin(), other.entityComponents.end());
			}
			this->lastEntityId = other.lastEntityId;
			other.entityComponents.clear();
			other.lastEntityId = 0;
		}
		return *this;
	}

	EntityManager::~EntityManager() {
		entityComponents.clear();
		for (const auto& typePair : entityComponents) {
			for (const auto componentPair : typePair.second) { 
				delete componentPair.second;
			}
		}
	}

	Component* EntityManager::getComponent(unsigned int entityId, std::type_index componentType) const noexcept
	{
		const auto entityList = entityComponents.find(componentType);
		if (entityList != entityComponents.end()) {
			const auto component = entityList->second.find(entityId);
			if (component != entityList->second.end()) return component->second;
		}
		return nullptr;
	}

	bool EntityManager::hasComponent(unsigned int entityId, std::type_index componentType) const  noexcept
	{
		const auto entityList = entityComponents.find(componentType);
		return entityList != entityComponents.end() && entityList->second.find(entityId) != entityList->second.end();
	}

	void EntityManager::removeComponentFromEntity(unsigned int entityId, std::type_index componentType)
	{
		try {
			delete entityComponents.at(componentType).at(entityId);
			entityComponents.at(componentType).erase(entityId);
			if (entityComponents.at(componentType).empty()) {
				entityComponents.erase(componentType);
			}
		}
		catch (const std::out_of_range&) {
			throw std::runtime_error(std::string("No component of type ") + componentType.name() + " found for entity " + std::to_string(entityId));
		}
	}

	void EntityManager::removeEntity(unsigned int entityId) {
		auto itr = entityComponents.begin();
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

	std::set<int> EntityManager::getAllEntities() const noexcept
	{
		std::set<int> entityIds;

		for (const auto& componentType : entityComponents) {
			for (const auto& test : componentType.second) {
				entityIds.insert(test.first);
			}
		}

		return entityIds;
	}

	EntityManager::EntityManager(const EntityManager& other)
	{
		lastEntityId = other.lastEntityId;
		for (auto it = other.entityComponents.begin(); it != other.entityComponents.end(); it++ )
		{
			std::unordered_map<unsigned int, Component*> newMap;
			for (auto itSub = it->second.begin(); itSub != it->second.end(); itSub++ )
			{
				newMap[itSub->first] = itSub->second->Clone();
			}
			entityComponents[it->first] = newMap;
		}
	}

	std::vector<Entity<Component*>> EntityManager::getAllEntitiesWithComponent(const std::type_index& componentType) const {
		std::vector<Entity<Component*>> result;
		try {
			auto const entities = entityComponents.at(componentType);

			result.reserve(entities.size());

			for (auto const& entry : entities) {
				Entity<Component*> entity{};
				entity.id = entry.first;
				entity.component = entry.second;

				result.push_back(entity);
			}
		
			return result;
		}
		catch (const std::out_of_range&) {} // No entities found, returning an empty array.
		return result;
	}


}
