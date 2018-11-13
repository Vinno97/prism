#pragma once

#include "Context.h"

#include "ECS/Systems/ResourceGatherSystem.h"


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
				auto playerInventory = entityManager->getComponent<InventoryComponent>(player.id);

				for (auto resourcePoint : resourcePoints) {
					auto resourcePointPosition = entityManager->getComponent<PositionComponent>(resourcePoint.id);
					
					if (ResourceGatherSystem::shouldIncreaseResources(*playerPosition, *resourcePointPosition)) {
						
						auto resource = entityManager->getComponent<ResourceSpawnComponent>(resourcePoint.id);
						
						increateResource(resource->resourceType, *playerInventory, resource->gatherRate);
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

		void ResourceGatherSystem::increateResource(std::string resourceType, InventoryComponent& playerInventory, int gatherRate)
		{
			if (resourceType == "red") {
				playerInventory.redResource += gatherRate;
				std::cout << "type " << resourceType << "- amount " << playerInventory.redResource << std::endl;
			}
			
			if (resourceType == "blue") {
				playerInventory.blueResource += gatherRate;
				std::cout << "type " << resourceType << "- amount " << playerInventory.blueResource << std::endl;
			}
			
			if (resourceType == "green") {
				playerInventory.greenResource += gatherRate;
				std::cout << "type " << resourceType << "- amount " << playerInventory.greenResource << std::endl;
			}
		}


	}
}