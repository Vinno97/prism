#pragma once

#include "Context.h"

#include "ECS/Systems/ResourceGatherSystem.h"
#include "ECS/Components/ResourceGatherComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/ResourceBlobComponent.h"

namespace ECS {
	namespace Systems {
		ResourceGatherSystem::ResourceGatherSystem(EntityManager & entityManager) : System(entityManager)
		{
			
		}
		ResourceGatherSystem::~ResourceGatherSystem()
			= default;

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

						
						increateResource(resource->resourceType, *playerInventory, (resource->gatherRate * context.deltaTime));
						
						if (resource->SpawnTimer >= 0.8f) {
							CreateBlob(resourcePoint.id, resource->resourceType);
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

		void ResourceGatherSystem::increateResource(std::string resourceType, InventoryComponent& playerInventory, float gatherRate)
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

		void ResourceGatherSystem::CreateBlob(int resourcePointID, std::string type) {
			
			auto blob = entityFactory.CreateBlob(*entityManager, type);
			auto bloblPosition = entityManager->getComponent<PositionComponent>(blob);
			bloblPosition->x = entityManager->getComponent<PositionComponent>(resourcePointID)->x;
			bloblPosition->y = entityManager->getComponent<PositionComponent>(resourcePointID)->y;
		}
	}
}