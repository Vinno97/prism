#pragma once

#include "Context.h"
#include <cmath>
#include <algorithm>

#include "ECS/Systems/ResourceGatherSystem.h"
#include "ECS/Components/ResourceGatherComponent.h"
#include "Enums/ResourceTypeEnum.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/TargetComponent.h"

namespace ECS
{
	namespace Systems
	{
		using namespace Components;

		void ResourceGatherSystem::update(Context& context)
		{
			auto resourceGatherers = entityManager->getAllEntitiesWithComponent<ResourceGatherComponent>();
			auto resourcePoints = entityManager->getAllEntitiesWithComponent<ResourceSpawnComponent>();

			for (auto resourcePoint : resourcePoints)
			{
				auto spawnComponent = entityManager->getComponent<ResourceSpawnComponent>(resourcePoint.id);
				if (spawnComponent->SpawnTimer < 0.8f)
				{
					spawnComponent->SpawnTimer += context.deltaTime;
					continue;
				}

				Math::Vector2<double> spawnPos = *entityManager->getComponent<PositionComponent>(resourcePoint.id);

				// Finds the nearest ResourceGatherer.
				auto gatherer = std::min_element(resourceGatherers.begin(), resourceGatherers.end(),
				                                 [&](auto e1, auto e2)
				                                 {
					                                 Math::Vector2<double> pos1 = *entityManager->getComponent<
						                                 PositionComponent>(e1.id);
					                                 Math::Vector2<double> pos2 = *entityManager->getComponent<
						                                 PositionComponent>(e2.id);
					                                 return distance(spawnPos, pos1) < distance(spawnPos, pos2);
				                                 });

				auto gathererPosition = entityManager->getComponent<PositionComponent>(gatherer->id);

				if (distance(spawnPos, static_cast<Math::Vector2<double>>(*gathererPosition)) <= 1.5)
				{
					spawnResourceBlob(spawnPos, gatherer->id, spawnComponent->resourceType,
					                  spawnComponent->value);
					spawnComponent->SpawnTimer = 0;
				}
			}
		}

		void ResourceGatherSystem::spawnResourceBlob(Math::Vector2<double> position, unsigned targetId,
		                                             Enums::ResourceType type, float value)
		{
			auto blob = entityFactory.createResourceBlob(*entityManager, type, value);
			auto positionComponent = entityManager->getComponent<PositionComponent>(blob);
			auto targetComponent = entityManager->getComponent<TargetComponent>(blob);
			targetComponent->target = targetId;
			positionComponent->x = position.x;
			positionComponent->y = position.y;
		}
	}
}
