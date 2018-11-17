#pragma once

#include "ECS/Systems/ResourceBlobSystem.h"
#include "ECS//Components/ResourceBlobComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "Math/Vector3f.h"
#include "ECS/Components/VelocityComponent.h"

namespace ECS {
	namespace Systems {
		ResourceBlobSystem::ResourceBlobSystem(EntityManager & entityManager) : System(entityManager)
		{
		}
		ResourceBlobSystem::~ResourceBlobSystem()
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

				RemoveBlobs(*playerLocation, *blobPosition, blob.id);
			}
		}

		void ResourceBlobSystem::RemoveBlobs(PositionComponent &playerPosition, PositionComponent &blobPosition, int blob) {

			auto x = blobPosition.x - playerPosition.x;
			auto y = blobPosition.y - playerPosition.y;

			float distance = sqrt((x*x) + (y*y));

			if (distance < 0.05f ) {
				entityManager->removeEntity(blob);
			}
			
		}
		System * ResourceBlobSystem::clone()
		{
			return nullptr;
		}
	}
}