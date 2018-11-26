#include <cmath>

#include "ECS/Systems/EnemyPathFindingSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "Math/Vector3f.h"

namespace ECS {
	namespace Systems {
		EnemyPathFindingSystem::EnemyPathFindingSystem(ECS::EntityManager &entityManager, float enemySpeed) : System(entityManager)
		{
			this->enemySpeed = enemySpeed;
		}

		EnemyPathFindingSystem::~EnemyPathFindingSystem()
			= default;

		void EnemyPathFindingSystem::update(Context& context)
		{
			unsigned int playerId;
			auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();
			if (players.size() > 0) {
				playerId = players[0].id;

				auto playerPosition = entityManager->getComponent<PositionComponent>(playerId);

				for (auto entity : entityManager->getAllEntitiesWithComponent<EnemyComponent>())
				{
					if (entityManager->hasComponent<PositionComponent>(entity.id) &&
						entityManager->hasComponent<VelocityComponent>(entity.id)) {

						auto enemyPosition = entityManager->getComponent<PositionComponent>(entity.id);
						auto enemyVelocity = entityManager->getComponent<VelocityComponent>(entity.id);

						Math::Vector3f vector = Math::Vector3f(playerPosition->x - enemyPosition->x, playerPosition->y - enemyPosition->y, 0);
						vector.normalize();
						enemyVelocity->dx += enemySpeed * vector.x * context.deltaTime;
						enemyVelocity->dy += enemySpeed * vector.y * context.deltaTime;
					}
				}
			}
		}

		std::unique_ptr<System> EnemyPathFindingSystem::clone()
		{
			return std::make_unique<EnemyPathFindingSystem>(EnemyPathFindingSystem(*entityManager,enemySpeed));
		}
	}
}
