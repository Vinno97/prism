#pragma once

#include <cmath>
#include "ECS/Systems/ResourceBlobSystem.h"
#include "ECS//Components/ResourceBlobComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "Math/Vector3f.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/ScoreComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/TargetComponent.h"
#include "ECS/Components/ResourceGatherComponent.h"
#include "Enums/ResourceTypeEnum.h"
#include "Util/DistanceUtil.h"
#include <algorithm>


namespace ECS {
	namespace Systems {
		using namespace Components;
		
		ResourceBlobSystem::ResourceBlobSystem(EntityManager & entityManager) : System(entityManager)
		{
		}

		void ResourceBlobSystem::update(Context & context)
		{
			auto resouceBlobs = entityManager->getAllEntitiesWithComponent<ResourceBlobComponent>();


			for (auto blob : resouceBlobs) {
                auto target = entityManager->getComponent<TargetComponent>(blob.id);
				
				auto blobPosition = entityManager->getComponent<PositionComponent>(blob.id);
                auto targetLocation = entityManager->getComponent<PositionComponent>(target->target);

				//When the target gets lost search for a new target
				if (targetLocation == nullptr) {
					Math::Vector2<double> spawnPos = *entityManager->getComponent<PositionComponent>(blob.id);
					auto resourceGatherers = entityManager->getAllEntitiesWithComponent<ResourceGatherComponent>();
					auto gatherer = std::min_element(resourceGatherers.begin(), resourceGatherers.end(), [&](auto e1, auto e2) {
						Math::Vector2<double> pos1 = *entityManager->getComponent<PositionComponent>(e1.id);
						Math::Vector2<double> pos2 = *entityManager->getComponent<PositionComponent>(e2.id);
						return Math::distance(spawnPos, pos1) < Math::distance(spawnPos, pos2);
					});
					target->target = gatherer->id;
					targetLocation = entityManager->getComponent<PositionComponent>(target->target);
				}

				auto blobVelocity = entityManager->getComponent<VelocityComponent>(blob.id);
				auto direction = Math::Vector3f{ float(targetLocation->x - blobPosition->x), float(targetLocation->y - blobPosition->y), 0.f };

				direction.normalize();
				direction = direction * 2;

				blobVelocity->dx = direction.x;
				blobVelocity->dy = direction.y;

				removeResourceBlobs(*targetLocation, *blobPosition, blob.id, context);
			}
		}

		void ResourceBlobSystem::removeResourceBlobs(PositionComponent &playerPosition, PositionComponent &blobPosition, int blob, Context & context) {

			auto x = blobPosition.x - playerPosition.x;
			auto y = blobPosition.y - playerPosition.y;

			float distance = std::sqrt((x*x) + (y*y));

			if (distance < 0.05f ) {
				Util::DistanceUtil distanceUtil;
				auto resource = entityManager->getComponent<ResourceBlobComponent>(blob);
				auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
				auto playerInventory = entityManager->getComponent<InventoryComponent>(player.id);
				increateResource(resource->resourceType, *playerInventory, resource->value);

				context.audioManager->playSound("Resource", distanceUtil.CalculateDistance(blobPosition.x, blobPosition.y, playerPosition.x, playerPosition.y));
				entityManager->removeEntity(blob);
			}
			
		}

		void ResourceBlobSystem::increateResource(Enums::ResourceType resourceType, InventoryComponent& playerInventory, float gatherRate)
		{
			auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
			auto score = entityManager->getComponent<ScoreComponent>(player.id);


			if (resourceType == Enums::ResourceType::RED ) {
				playerInventory.redResource += gatherRate;
				score->gatheredRedResources++;
			}

			if (resourceType == Enums::ResourceType::BLUE) {
				playerInventory.blueResource += gatherRate;
				score->gatheredBlueResources++;
			}

			if (resourceType == Enums::ResourceType::GREEN) {
				playerInventory.greenResource += gatherRate;
				score->gatheredGreenResources++;
			}
		}
	}
}
