#include "ECS/Systems/EnemySpawnSystem.h"
#include "ECS/Components/EnemySpawnComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/TargetComponent.h"
#include "ECS/Components/PlayerComponent.h"

namespace ECS {
	namespace Systems {
		using namespace Components;

		EnemySpawnSystem::EnemySpawnSystem(EntityManager& entityManager) : System(entityManager) {
		}

		EnemySpawnSystem::~EnemySpawnSystem()
			= default;

		void EnemySpawnSystem::update(Context& context) {

			for (const auto& spawnPoint : entityManager->getAllEntitiesWithComponent<EnemySpawnComponent>()) {
				auto component = spawnPoint.component;

				if (!component->enabled) return;

				component->timeSinceLastSpawn += context.deltaTime;

				if (component->timeSinceLastSpawn > component->spawnInterval) {
					component->timeSinceLastSpawn = 0;
					auto position = entityManager->getComponent<PositionComponent>(spawnPoint.id);
					auto enemy = entityFactory.createEnemy(*entityManager);
					auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
					entityManager->getComponent<PositionComponent>(enemy)->x += position->x+1;
					entityManager->getComponent<PositionComponent>(enemy)->y += position->y+1;
					entityManager->getComponent<TargetComponent>(enemy)->target = player.id;
				}
			}
		}
	}
}
