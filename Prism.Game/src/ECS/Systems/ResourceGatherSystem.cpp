#pragma once

#include "Context.h"

#include "ECS/Systems/ResourceGatherSystem.h"
#include "ECS/Components/ResourceGatherComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/ResourceBlobComponent.h"
#include "Enums/ResourceTypeEnum.h"

namespace ECS {
	namespace Systems {
		ResourceGatherSystem::ResourceGatherSystem(EntityManager & entityManager) : System(entityManager)
		{
			
		}

		void ResourceGatherSystem::update(Context& context)
		{
			auto resourceGatheres = entityManager->getAllEntitiesWithComponent<ResourceGatherComponent>();
			auto resourcePoints = entityManager->getAllEntitiesWithComponent<ResourceSpawnComponent>();
			auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>();
			auto playerInventory = entityManager->getComponent<InventoryComponent>(player[0].id);

			for (auto resourceGatherer : resourceGatheres) {
				
				auto resourceGatherPosition = entityManager->getComponent<PositionComponent>(resourceGatherer.id);
				
				for (auto resourcePoint : resourcePoints) {

					auto resourcePointPosition = entityManager->getComponent<PositionComponent>(resourcePoint.id);
					auto range = entityManager->getComponent<ResourceGatherComponent>(resourceGatherer.id)->gatherRange;

					if (ResourceGatherSystem::shouldIncreaseResources(*resourceGatherPosition, *resourcePointPosition, range )) {
						
						auto resource = entityManager->getComponent<ResourceSpawnComponent>(resourcePoint.id);
												
						//increateResource(resource->resourceType, *playerInventory, (resource->gatherRate * context.deltaTime));
						
						if (resource->SpawnTimer >= 0.8f) {
							CreateBlob(resourcePoint.id, resource->resourceType, resource->value);
							resource->SpawnTimer = 0;
						}
						resource->SpawnTimer += context.deltaTime;
					}

				}
			}
		}
		System * ResourceGatherSystem::clone()
		{
			auto newSystem = new ResourceGatherSystem(*entityManager);
			return newSystem;
		}
		bool ResourceGatherSystem::shouldIncreaseResources(PositionComponent& playerPosition, PositionComponent& resourcePointPosition, float radius)
		{
			auto x = resourcePointPosition.x - playerPosition.x;
			auto y = resourcePointPosition.y - playerPosition.y;

			float distance = sqrt((x*x) + (y*y));

			if (distance < radius) {
				return true;
			}

			return false;
		}

		void ResourceGatherSystem::CreateBlob(int resourcePointID, Enums::ResourceType type, float value) {
			
			auto blob = entityFactory.CreateBlob(*entityManager, type, value);
			auto bloblPosition = entityManager->getComponent<PositionComponent>(blob);
			bloblPosition->x = entityManager->getComponent<PositionComponent>(resourcePointID)->x;
			bloblPosition->y = entityManager->getComponent<PositionComponent>(resourcePointID)->y;
		}
	}
}