#include "ECS/Systems/EnemyPathFindingSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"

namespace ECS {
	namespace Systems {
		EnemyPathFindingSystem::EnemyPathFindingSystem(ECS::EntityManager &entityManager, float enemySpeed) : System(entityManager)
		{
			this->enemySpeed = enemySpeed;
		}

		EnemyPathFindingSystem::~EnemyPathFindingSystem()
			= default;

		void EnemyPathFindingSystem::update(Context context)
		{
			unsigned int playerId;
			auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();
			if (players.size() > 0) {
				playerId = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0].id;

				auto playerPosition = entityManager->getComponent<PositionComponent>(playerId);

				for (auto entity : entityManager->getAllEntitiesWithComponent<EnemyComponent>())
				{
					if (entityManager->hasComponent<PositionComponent>(entity.id) &&
						entityManager->hasComponent<VelocityComponent>(entity.id)) {

						auto enemyPosition = entityManager->getComponent<PositionComponent>(entity.id);
						auto enemyVelocity = entityManager->getComponent<VelocityComponent>(entity.id);

						float x = playerPosition->x - enemyPosition->x;
						float y = playerPosition->y - enemyPosition->y;

						float dirX = x / std::abs(x);
						float dirY = y / std::abs(y);

						auto angle = std::abs(std::atan(y / x));

						enemyVelocity->dx += enemySpeed * std::cos(angle) * dirX * context.deltaTime;
						enemyVelocity->dy += enemySpeed * std::sin(angle) * dirY * context.deltaTime;
					}
				}
			}
		}

		ECS::Systems::System* EnemyPathFindingSystem::clone()
		{
			return new EnemyPathFindingSystem(*entityManager,enemySpeed);
		}
	}
}
