#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/PositionComponent.h"



namespace ECS {
	namespace Systems {
		using namespace Components;

		AttackSystem::AttackSystem(EntityManager &entityManager) : System(entityManager) { }

		AttackSystem::~AttackSystem()
			= default;

		void AttackSystem::update(Context& context) {

			for (auto entity : entityManager->getAllEntitiesWithComponent<EnemyComponent>())
			{
				if (entityManager->hasComponent<PositionComponent>(entity.id)
					&& entityManager->hasComponent<BoundingBoxComponent>(entity.id)
					&& entityManager->hasComponent<VelocityComponent>(entity.id)
					&& entityManager->hasComponent<HealthComponent>(entity.id)) {

					auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(entity.id);
					auto Position = entityManager->getComponent<PositionComponent>(entity.id);

					boundingBoxComponent->boundingBox.SetPosXY(Position->x, Position->y);
					std::vector<unsigned int> vector;

					vector = boundingBoxComponent->collidesWith;
					if (boundingBoxComponent->didCollide) {

						for (int i = 0; i < vector.size(); i++) {
							if (entityManager->hasComponent<HealthComponent>(vector[i])) {
								updateEntity(vector[i], context);
								updateEntity(entity.id, context);
								context.audioManager->playSound("EnemyKill", 0);
							}
						}
					}
				}
			}
		}

		void AttackSystem::updateEntity(int id, Context& context) {
			if (entityManager->hasComponent<EnemyComponent>(id)) {
				entityManager->removeEntity(id);
				// Print (Remove after review)
				std::cout << "Enemy is exploded" << std::endl;
			}

			if (entityManager->hasComponent<HealthComponent>(id)) {
				auto currentComponent = entityManager->getComponent<HealthComponent>(id);

				currentComponent->currentHealth -= 10;

				if (!entityManager->hasComponent<PlayerComponent>(id) && currentComponent->currentHealth <= 0) {
					//context.stateMachine->setState<EndState>();
					entityManager->removeEntity(id);
				}

				// Print (Remove after review)
				std::cout << "Speler: " << currentComponent->currentHealth << std::endl;
			}
		}
	}
}

