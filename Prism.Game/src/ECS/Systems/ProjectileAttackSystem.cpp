#include "ECS/Systems/ProjectileAttackSystem.h"
#include "ECS/Components/ProjectileAttackComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/ScoreComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "Util/DistanceUtil.h"
#include <cmath>

namespace ECS {
	namespace Systems {
		using namespace Components;
		
		ProjectileAttackSystem::ProjectileAttackSystem(EntityManager& entityManager) : System(entityManager)
		{
		}

		ProjectileAttackSystem::~ProjectileAttackSystem()
			= default;

		void ProjectileAttackSystem::update(Context& context)
		{
			auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
			auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();

			for (auto entity : entityManager->getAllEntitiesWithComponent<ProjectileAttackComponent>()) {
				auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);

				if (entityManager->getComponent<ProjectileAttackComponent>(entity.id) && boundingBoxComponent->didCollide) {
				
					auto vector = boundingBoxComponent->collidesWith;
					bool isEnemy = false;
					for (auto collider : vector) {
						
						if (entityManager->hasComponent<EnemyComponent>(collider)) {
							isEnemy = true;

							if (entityManager->hasComponent<HealthComponent>(entity.id) && entityManager->hasComponent<HealthComponent>(collider)) {
								auto ProjectileHealth = entityManager->getComponent<HealthComponent>(entity.id);
								auto EnemyHealth = entityManager->getComponent<HealthComponent>(collider);
								int tempEnemyHealth = EnemyHealth->currentHealth;
								EnemyHealth->currentHealth -= ProjectileHealth->currentHealth;
								ProjectileHealth->currentHealth -= tempEnemyHealth;
								if (ProjectileHealth->currentHealth <= 0) {
									entityManager->removeEntity(entity.id);
								}
								if (EnemyHealth->currentHealth <= 0) {

									auto scoreComponent = entityManager->getComponent<ScoreComponent>(player.id);
									scoreComponent->killedEnemies += 1;

									entityManager->removeEntity(collider);
									Util::DistanceUtil distanceUtil;
									int BoxX = boundingBoxComponent->boundingBox.GetPosX();
									int BoxY = boundingBoxComponent->boundingBox.GetPosY();
									int PlayerX = entityManager->getComponent<PositionComponent>(players[0].id)->x;
									int PlayerY = entityManager->getComponent<PositionComponent>(players[0].id)->x;
									context.audioManager->playSound("EnemyKill", distanceUtil.CalculateDistance(BoxX, BoxY, PlayerX, PlayerY));
									break;
								}
							}
						}
					}
					if (!isEnemy) {
						entityManager->removeEntity(entity.id);
					}
				}

				// TODO: Wat doet deze code hier eigenlijk? De game crasht hierop, maar werkt correct als het uitgeschakeld staat. 
				// Ik kan me ook niet bedenken wat dit zou horen te doen.
				// boundingBoxComponent->didCollide = false;
				// boundingBoxComponent->collidesWith.clear();
			}
		}
	}
}
