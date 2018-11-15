#include "ECS/Systems/ProjectileAttackSystem.h"
#include "ECS/Components/ProjectileAttackComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/HealthComponent.h"

namespace ECS {
	namespace Systems {
		ProjectileAttackSystem::ProjectileAttackSystem(EntityManager& entityManager) : System(entityManager)
		{
		}

		ProjectileAttackSystem::~ProjectileAttackSystem()
			= default;

		void ProjectileAttackSystem::update(Context context)
		{
			
			for (auto entity : entityManager->getAllEntitiesWithComponent<ProjectileAttackComponent>()) {
				auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);

				if (entityManager->getComponent<ProjectileAttackComponent>(entity.id) && boundingBoxComponent->didCollide) {
				
					auto vector = boundingBoxComponent->collidesWith;

					for (auto collider : vector) {
						for (auto enemy : entityManager->getAllEntitiesWithComponent<EnemyComponent>()) {
							auto other = entityManager->getComponent<BoundingBoxComponent>(enemy.id);
							if (std::addressof(*collider) == std::addressof(other->boundingBox)){
								if (entityManager->hasComponent<HealthComponent>(entity.id)) {
									auto health = entityManager->getComponent<HealthComponent>(entity.id);
									boundingBoxComponent->didCollide = false;
									boundingBoxComponent->collidesWith.clear();
									if (health->health <= 0) {
										entityManager->removeEntity(entity.id);
										
									}
								}
								if (entityManager->hasComponent<HealthComponent>(enemy.id)) {
									auto health = entityManager->getComponent<HealthComponent>(enemy.id);
									if (health->health <= 0) {
										
										entityManager->removeEntity(enemy.id);
									}
								}
							}
						}
						
					}

				}

			}

		}

		System * ProjectileAttackSystem::clone()
		{
			return new ProjectileAttackSystem(*entityManager);
		}
	}
}