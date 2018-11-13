#include "ECS/Systems/EnemySpawnSystem.h"
#include "ECS/Components/EnemySpawnComponent.h"
#include "EntityFactory.h"
#include "Context.h"
#include "InputManager.h"

namespace ECS {
	namespace Systems {
		EnemySpawnSystem::EnemySpawnSystem(EntityManager& entityManager) : System(entityManager) {
		}

		EnemySpawnSystem::~EnemySpawnSystem()
			= default;

		void EnemySpawnSystem::update(Context context) {
			auto time = context.deltaTime;
			auto input = context.inputManager;
			EntityFactory entityFactory;

			for (const auto& spawnPoint : entityManager->getAllEntitiesWithComponent<EnemySpawnComponent>()) {
				auto component = spawnPoint.component;

				if (!component->enabled)
					return;

				auto position = entityManager->getComponent<PositionComponent>(spawnPoint.id);

				component->timeSinceLastSpawn += time;

				if (component->timeSinceLastSpawn > component->spawnInterval) {
					component->timeSinceLastSpawn = 0;
					auto enemy = entityFactory.createEnemy(*entityManager);
					entityManager->getComponent<PositionComponent>(enemy)->x += position->x+0.5;
					entityManager->getComponent<PositionComponent>(enemy)->y += position->y+0.5;
				}
			}
		}
		System * EnemySpawnSystem::clone()
		{
			return new EnemySpawnSystem(*entityManager);
		}
	}
}
