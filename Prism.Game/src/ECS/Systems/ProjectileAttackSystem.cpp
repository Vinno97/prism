#include "ECS/Systems/ProjectileAttackSystem.h"
#include "ECS/Components/ProjectileAttackComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/PlayerComponent.h"

namespace ECS {
	namespace Systems {
		ProjectileAttackSystem::ProjectileAttackSystem(EntityManager& entityManager) : System(entityManager)
		{
		}

		ProjectileAttackSystem::~ProjectileAttackSystem()
			= default;

		void ProjectileAttackSystem::update(Context& context)
		{
			auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();

			for (auto entity : entityManager->getAllEntitiesWithComponent<ProjectileAttackComponent>()) {
				auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);

				if (entityManager->getComponent<ProjectileAttackComponent>(entity.id) && boundingBoxComponent->didCollide) {
				
					auto vector = boundingBoxComponent->collidesWith;
					bool isEnemy = false;
					for (auto collider : vector) {
						
						for (auto enemy : entityManager->getAllEntitiesWithComponent<EnemyComponent>()) {
							auto other = entityManager->getComponent<BoundingBoxComponent>(enemy.id);
							if (std::addressof(*collider) == std::addressof(other->boundingBox)){
								isEnemy = true;
								
								
								if (entityManager->hasComponent<HealthComponent>(entity.id) && entityManager->hasComponent<HealthComponent>(enemy.id)) {
									auto ProjectileHealth = entityManager->getComponent<HealthComponent>(entity.id);
									auto EnemyHealth = entityManager->getComponent<HealthComponent>(enemy.id);
									int tempEnemyHealth = EnemyHealth->health;
									EnemyHealth->health -= ProjectileHealth->health;
									ProjectileHealth->health -= tempEnemyHealth;
									if (ProjectileHealth->health <= 0) {
										entityManager->removeEntity(entity.id);
									}
									if (EnemyHealth->health <= 0) {
										entityManager->removeEntity(enemy.id);
										break;
									}
								}
							}
						}
						
						
					}
					if (!isEnemy) {
						entityManager->removeEntity(entity.id);
					}
				}
				boundingBoxComponent->didCollide = false;
				boundingBoxComponent->collidesWith.clear();
			}

		}

		System * ProjectileAttackSystem::clone()
		{
			return new ProjectileAttackSystem(*entityManager);
		}
	}
}