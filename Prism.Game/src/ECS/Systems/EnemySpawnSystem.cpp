#include "ECS/Systems/EnemySpawnSystem.h"
#include "ECS/Components/EnemySpawnComponent.h"
#include "Context.h"
#include "InputManager.h"
#include "ECS/Components/PositionComponent.h"

namespace ECS {
	namespace Systems {
		using namespace Components;

		EnemySpawnSystem::EnemySpawnSystem(EntityManager& entityManager) : System(entityManager) {
		}

		EnemySpawnSystem::~EnemySpawnSystem()
			= default;

		void EnemySpawnSystem::update(Context& context) {
			auto time = context.deltaTime;
			auto input = context.inputManager;

			for (const auto& spawnPoint : entityManager->getAllEntitiesWithComponent<EnemySpawnComponent>()) {
				auto component = spawnPoint.component;

				if (!component->enabled)
					return;

				auto position = entityManager->getComponent<PositionComponent>(spawnPoint.id);

				component->timeSinceLastSpawn += time;

				if (component->timeSinceLastSpawn > component->spawnInterval) {
					component->timeSinceLastSpawn = 0;
					auto enemy = EntityFactory::getInstance().createEnemy(*entityManager);
					entityManager->getComponent<PositionComponent>(enemy)->x += position->x+1;
					entityManager->getComponent<PositionComponent>(enemy)->y += position->y+1;
				}
			}
		}
	}
}
