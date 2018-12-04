#pragma once

#include <cmath>
#include "ECS/Systems/ResourceCollectionSystem.h"
#include "ECS//Components/ResourceBlobComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "Math/Vector3.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/TargetComponent.h"
#include "Enums/ResourceTypeEnum.h"

namespace ECS {
	namespace Systems {
		using namespace Components;
		
		ResourceBlobSystem::ResourceBlobSystem(EntityManager & entityManager) : System(entityManager)
		{
		}

		void ResourceBlobSystem::update(Context & context)
		{
			auto resourceBlobs = entityManager->getAllEntitiesWithComponent<ResourceBlobComponent>();

			for (auto blob : resourceBlobs) {
                auto target = entityManager->getComponent<TargetComponent>(blob.id);
				Math::Vector2d blobPosition = *entityManager->getComponent<PositionComponent>(blob.id);
				Math::Vector2d targetPosition = *entityManager->getComponent<PositionComponent>(target->target);

				if (Math::distance(blobPosition, targetPosition) < 0.05f ) {
					auto resource = entityManager->getComponent<ResourceBlobComponent>(blob.id);
					auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
					auto playerInventory = entityManager->getComponent<InventoryComponent>(player.id);
					increaseResource(resource->resourceType, *playerInventory, resource->value);

					context.audioManager->playSound("Resource");
					entityManager->removeEntity(blob.id);
				}
			}
		}

		void ResourceBlobSystem::increaseResource(Enums::ResourceType resourceType, InventoryComponent &inventory,
		                                          float gatherRate)
		{
			if (resourceType == Enums::ResourceType::RED ) {
				inventory.redResource += gatherRate;
			}

			if (resourceType == Enums::ResourceType::BLUE) {
				inventory.blueResource += gatherRate;
			}

			if (resourceType == Enums::ResourceType::GREEN) {
				inventory.greenResource += gatherRate;
			}
		}
	}
}
