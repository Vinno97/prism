#pragma once

#include <cmath>
#include "ECS/Systems/ResourceBlobSystem.h"
#include "ECS//Components/ResourceBlobComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "Math/Vector3f.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "Enums/ResourceTypeEnum.h"

namespace ECS {
	namespace Systems {
		using namespace Components;
		
		ResourceBlobSystem::ResourceBlobSystem(EntityManager & entityManager) : System(entityManager)
		{
		}

		void ResourceBlobSystem::update(Context & context)
		{
			auto resouceBlobs = entityManager->getAllEntitiesWithComponent<ResourceBlobComponent>();
			auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
			auto playerLocation = entityManager->getComponent<PositionComponent>(player.id);

			for (auto blob : resouceBlobs) {

				auto blobPosition = entityManager->getComponent<PositionComponent>(blob.id);

				auto blobVelocity = entityManager->getComponent<VelocityComponent>(blob.id);
				auto direction = Math::Vector3f{ float(playerLocation->x - blobPosition->x), float(playerLocation->y - blobPosition->y), 0.f };

				direction.normalize();

				blobVelocity->dx = direction.x;
				blobVelocity->dy = direction.y;

				removeResourceBlobs(*playerLocation, *blobPosition, blob.id, context);
			}
		}

		void ResourceBlobSystem::removeResourceBlobs(PositionComponent &playerPosition, PositionComponent &blobPosition, int blob, Context & context) {

			auto x = blobPosition.x - playerPosition.x;
			auto y = blobPosition.y - playerPosition.y;

			float distance = std::sqrt((x*x) + (y*y));

			if (distance < 0.05f ) {
				
				
				auto resource = entityManager->getComponent<ResourceBlobComponent>(blob);
				auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
				auto playerInventory = entityManager->getComponent<InventoryComponent>(player.id);
				increateResource(resource->resourceType, *playerInventory, resource->value );

				context.audioManager->playSound("Resource");
				entityManager->removeEntity(blob);
			}
			
		}

		void ResourceBlobSystem::increateResource(Enums::ResourceType resourceType, InventoryComponent& playerInventory, float gatherRate)
		{
			if (resourceType == Enums::ResourceType::RED ) {
				playerInventory.redResource += gatherRate;
				//std::cout << "type " << resourceType << "- amount " << playerInventory.redResource << std::endl;
			}

			if (resourceType == Enums::ResourceType::BLUE) {
				playerInventory.blueResource += gatherRate;
				//std::cout << "type " << resourceType << "- amount " << playerInventory.blueResource << std::endl;
			}

			if (resourceType == Enums::ResourceType::GREEN) {
				playerInventory.greenResource += gatherRate;
				//std::cout << "type " << resourceType << "- amount " << playerInventory.greenResource << std::endl;
			}
		}
	}
}
