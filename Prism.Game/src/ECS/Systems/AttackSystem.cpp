#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "Renderer/Animation.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/AnimationComponent.h"


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
							if (entityManager->hasComponent<HealthComponent>(vector[i]) && !entityManager->hasComponent<EnemyComponent>(vector[i])) {
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
				if(entityManager->hasComponent<AnimationComponent>(id))
				{
					auto c = entityManager->getComponent<AnimationComponent>(id);
					c->currentAnimations[Renderer::Animation::Expand] = std::make_tuple<float, bool>(100.f, true);
				}

				entityManager->removeComponentFromEntity<EnemyComponent>(id);
				entityManager->removeComponentFromEntity<VelocityComponent>(id);
				entityManager->removeComponentFromEntity<HealthComponent>(id);
			}

			if (entityManager->hasComponent<HealthComponent>(id)) {
				auto currentComponent = entityManager->getComponent<HealthComponent>(id);

				currentComponent->currentHealth -= 10;

				if (!entityManager->hasComponent<PlayerComponent>(id) && currentComponent->currentHealth <= 0) {
					entityManager->removeEntity(id);
				}
			}
		}
	}
}

