#include "ECS/Systems/TowerAimingSystem.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS//Components/TowerComponent.h"
#include "ECS/Components/ShootingComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "Math/Vector3f.h"

using namespace ECS;
using namespace Systems;

ECS::Systems::TowerAimingSystem::TowerAimingSystem(EntityManager & entityManager) : System(entityManager)
{
}

void ECS::Systems::TowerAimingSystem::update(Context & context)
{
	auto enemyList = entityManager->getAllEntitiesWithComponent<EnemyComponent>();
	auto towerList = entityManager->getAllEntitiesWithComponent<TowerComponent>();

	for (const auto& tower : towerList) {

		auto towerPosition = entityManager->getComponent<PositionComponent>(tower.id);

		for (const auto& enemy : enemyList) {

			auto enemyPosition = entityManager->getComponent<PositionComponent>(enemy.id);
			auto enemeySpeed = entityManager->getComponent<VelocityComponent>(enemy.id);
			auto shootingComponent = entityManager->getComponent<ShootingComponent>(tower.id);

			if (enemyIsInRange(*towerPosition, *enemyPosition, radius)) {

				auto directionx = (enemyPosition->x + enemeySpeed->dx * (context.deltaTime * 10)) - towerPosition->x;
				auto directiony = (enemyPosition->y + enemeySpeed->dy * (context.deltaTime * 10)) - towerPosition->y;
				Math::Vector3f vec = Math::Vector3f(directionx, directiony, 0);
				vec.normalize();

				shootingComponent->xdirection = vec.x;
				shootingComponent->ydirection = vec.y;
				
				shootingComponent->isShooting = true;
			}
			else {
				shootingComponent->isShooting = false;
			}
		}
	}

}

bool TowerAimingSystem::enemyIsInRange(PositionComponent& playerPosition, PositionComponent& resourcePointPosition, float radius) const
{
	auto x = resourcePointPosition.x - playerPosition.x;
	auto y = resourcePointPosition.y - playerPosition.y;

	float distance = sqrt((x*x) + (y*y));

	if (distance < radius) {
		return true;
	}

	return false;
}

//System * ECS::Systems::TowerAimingSystem::clone()
//{
//	return nullptr;
//}
