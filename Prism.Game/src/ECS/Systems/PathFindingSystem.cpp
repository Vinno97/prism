#include "ECS/Systems/PathFindingSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;

PathFindingSystem::PathFindingSystem(ECS::EntityManager &entityManager) : System(entityManager)
{
}

PathFindingSystem::~PathFindingSystem()
{
}

void PathFindingSystem::update(Context context)
{
	unsigned int playerId;
	auto players = &entityManager->getAllEntitiesWithComponent<PlayerComponent>();
	if (players->size() > 0) {
		playerId = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0].id;

		auto playerPosition = entityManager->getComponent<PositionComponent>(playerId);

		for (auto entity : entityManager->getAllEntitiesWithComponent<EnemyComponent>())
		{
			if (entityManager->hasComponent<PositionComponent>(entity.id) &&
				entityManager->hasComponent<VelocityComponent>(entity.id)) {

				auto enemyPosition = entityManager->getComponent<PositionComponent>(entity.id);
				auto enemyVelocity = entityManager->getComponent<VelocityComponent>(entity.id);

				auto x = enemyPosition->x - playerPosition->x;
			}
		}
	}
}

ECS::Systems::System* PathFindingSystem::clone()
{
}
