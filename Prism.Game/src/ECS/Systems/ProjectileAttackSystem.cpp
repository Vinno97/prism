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
#include "ECS/Components/AnimationComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "Math/Vector2.h"

namespace ECS {
	namespace Systems {
		using namespace Components;
		using namespace Math;
		
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
					boundingBoxComponent->didCollide = false;
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

									Vector2d ePos = *entityManager->getComponent<PositionComponent>(collider);
									Vector2d pPos = *entityManager->getComponent<PositionComponent>(players[0].id);

									context.audioManager->playSound("EnemyKill", Math::distance(ePos, pPos));

									if (entityManager->hasComponent<AnimationComponent>(collider))
									{
										auto c = entityManager->getComponent<AnimationComponent>(collider);
										c->currentAnimations[Renderer::Animation::Expand] = std::make_tuple<float, bool>(100.f, true);
									}
									entityManager->removeComponentFromEntity<EnemyComponent>(collider);
									entityManager->removeComponentFromEntity<VelocityComponent>(collider);
									entityManager->removeComponentFromEntity<HealthComponent>(collider);

									break;
								}
							}
						}

					}

					if (!isEnemy) {
						//boundingBoxComponent->didCollide = false;
						//boundingBoxComponent->collidesWith.clear();
						entityManager->removeEntity(entity.id);
					}
				}
			}
		}
	}
}
