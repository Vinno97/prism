#include "ECS/Systems/EnemySpawnSystem.h"
#include "ECS/Components/EnemySpawnComponent.h"
#include "Context.h"
#include "InputManager.h"
#include "ECS/Components/PositionComponent.h"
#include <random>

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

			if (timeSinceLastWave >= timeToNextWave)
			{
				timeSinceLastWave = 0.f;
				waveIsOngoing = true;
				waveDuration += 0.8f;
			}

			if(!waveIsOngoing)
			{
				timeSinceLastWave += time;
			} else {
				currentWaveLength += time;
				if(currentWaveLength >= waveDuration)
				{
					waveIsOngoing = false;
					currentWaveLength = 1.0f;
				}

				for (const auto& spawnPoint : entityManager->getAllEntitiesWithComponent<EnemySpawnComponent>()) {
					auto component = spawnPoint.component;


					if (!component->enabled)
						return;

					auto position = entityManager->getComponent<PositionComponent>(spawnPoint.id);

					component->timeSinceLastSpawn += time;

					if (component->timeSinceLastSpawn > 0.3f) {
						component->timeSinceLastSpawn = 0;
						auto enemy = EntityFactory::getInstance().createEnemy(*entityManager);
						entityManager->getComponent<PositionComponent>(enemy)->x += position->x + (rand() % 3) - 1;
						entityManager->getComponent<PositionComponent>(enemy)->y += position->y + (rand() % 3) - 1;
					}
				}
			}
		}
	}
}
