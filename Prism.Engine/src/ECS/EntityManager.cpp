#include "ECS/EntityManager.h"
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <string>

#include "ECS/Components/PositionComponent.h"

namespace ECS
{
	using namespace Components;

	Component* EntityManager::getComponent(unsigned int entityId, std::type_index componentType) const noexcept
	{
		auto&& entityList = entityComponents.find(componentType);
		if (entityList != entityComponents.end())
		{
			const auto component = entityList->second.find(entityId);
			if (component != entityList->second.end()) return component->second.get();
		}
		return nullptr;
	}

	bool EntityManager::hasComponent(unsigned int entityId, std::type_index componentType) const noexcept
	{
		const auto entityList = entityComponents.find(componentType);
		return entityList != entityComponents.end() && entityList->second.find(entityId) != entityList->second.end();
	}

	EntityManager& EntityManager::removeComponentFromEntity(unsigned int entityId, std::type_index componentType)
	{
		auto&& entityList = entityComponents.find(componentType);
		if (entityList != entityComponents.end())
		{
			entityList->second.erase(entityId);
			if (entityList->second.empty())
			{
				entityComponents.erase(componentType);
			}
		}
		return *this;
	}

	EntityManager& EntityManager::removeEntity(unsigned int entityId)
	{
		auto&& itr = entityComponents.begin();
		while (itr != entityComponents.end())
		{
			itr->second.erase(entityId);

			if (itr->second.empty())
			{
				itr = entityComponents.erase(itr);
			}
			else
			{
				++itr;
			}
		}
		return *this;
	}

	std::set<int> EntityManager::getAllEntities() const noexcept
	{
		std::set<int> entityIds;

		for (const auto& componentType : entityComponents)
		{
			for (const auto& test : componentType.second)
			{
				entityIds.insert(test.first);
			}
		}

		return entityIds;
	}

	std::vector<Entity<Component*>> EntityManager::getAllEntitiesWithComponent(
		const std::type_index& componentType) const
	{
		std::vector<Entity<Component*>> result;
		auto&& entityList = entityComponents.find(componentType);
		if (entityList != entityComponents.end())
		{
			result.reserve(entityList->second.size());

			for (auto const& entry : entityList->second)
			{
				Entity<Component*> entity{};
				entity.id = entry.first;
				entity.component = entry.second.get();

				result.push_back(entity);
			}
		}
		return result;
	}
}
