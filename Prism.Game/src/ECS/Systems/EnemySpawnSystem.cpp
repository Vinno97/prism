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
			auto input = context.inputManager;
			if (input->isKeyPressed(Key::KEY_Q)) {
				for (const auto& player : entityManager->getAllEntitiesWithComponent<EnemySpawnComponent>()) {
					EntityFactory entityFactory;
						auto enemy = entityFactory.createEnemy(*entityManager);
						entityManager->getComponent<PositionComponent>(enemy)->x += 1;
				}
			}
		}
		System * EnemySpawnSystem::clone()
		{
			return new EnemySpawnSystem(*entityManager);
		}
	}
}
