#pragma once

#include "Context.h"

#include "ECS/Systems/ResourceGatherSystem.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"

namespace ECS {
	namespace Systems {
		ResourceGatherSystem::ResourceGatherSystem(EntityManager & entityManager) : System(entityManager)
		{
		}
		ResourceGatherSystem::~ResourceGatherSystem()
			= default;

		void ResourceGatherSystem::update(Context context)
		{
			auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();
			auto resourcePoints = entityManager->getAllEntitiesWithComponent<ResourceSpawnComponent>();

			for (auto player : players) {
				auto playerPosition = entityManager->getComponent<PositionComponent>(player.id);

				for (auto resourcePoint : resourcePoints) {
					auto resourcePointPosition = entityManager->getComponent<PositionComponent>(resourcePoint.id);
					
					if (ResourceGatherSystem::shouldIncreaseResources(*playerPosition, *resourcePointPosition)) {
						auto resource = entityManager->getComponent<ResourceSpawnComponent>(resourcePoint.id);
						resource->currentStock -= 10;
						
					}
				}
			}
		}
		System * ResourceGatherSystem::clone()
		{
			auto newSystem = new ResourceGatherSystem(*entityManager);
			return newSystem;
		}
		bool ResourceGatherSystem::shouldIncreaseResources(PositionComponent& playerPosition, PositionComponent& resourcePointPosition)
		{
			if (fabs((playerPosition.x - resourcePointPosition.x)) < xMargin && fabs((playerPosition.y - resourcePointPosition.y)) < yMargin) {
				return true;
			}
			return false;
		}
	}
}