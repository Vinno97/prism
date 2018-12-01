#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "StateMachine.h"
#include "States/EndState.h"
#include "States/PauseState.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"


ECS::Systems::AttackSystem::AttackSystem(EntityManager &entityManager) : System(entityManager) { }

ECS::Systems::AttackSystem::~AttackSystem()
= default;

using namespace States;

void ECS::Systems::AttackSystem::update(Context& context) {

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
					if(!entityManager->hasComponent<EnemyComponent>(vector[i])){
						updateEntity(vector[i],context);
						updateEntity(entity.id,context);
						context.audioManager->playSound("EnemyKill");
					}
				}
			}
		}
	}
}

void ECS::Systems::AttackSystem::updateEntity(int id, Context& context) {
	if (entityManager->hasComponent<EnemyComponent>(id)) {
		entityManager->removeEntity(id);
		// Print (Remove after review)
		std::cout << "Enemy is exploded" << std::endl;
	}

	if (entityManager->hasComponent<HealthComponent>(id)) {
		auto currentComponent = entityManager->getComponent<HealthComponent>(id);

		currentComponent->health -= 10;

		if (currentComponent->health <= 0) {

			// Print (Remove after review)
			std::cout << "Player is dead" << std::endl;

			if (entityManager->hasComponent<PlayerComponent>(id)) {
				context.stateMachine->setState<EndState>();
			}
			else {
				entityManager->removeEntity(id);
			}

		}
		// Print (Remove after review)
		std::cout << "Speler: " << currentComponent->health << std::endl;
	}
}

