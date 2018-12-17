#include <math.h>
#include "ECS/Systems/GameOverSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "StateMachine.h"
#include "States/EndState.h"
#include "States/PrismGame.h"
#include "ECS/Components/ScoreComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"

namespace ECS {
	namespace Systems {
		using namespace Components;
		using namespace States;

		GameOverSystem::GameOverSystem(EntityManager &entityManager) : System(entityManager) { }

		void ECS::Systems::GameOverSystem::update(Context& context) {
			for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
				auto healthComponent = entityManager->getComponent<HealthComponent>(entity.id);
				
				if (healthComponent->currentHealth > 30 && health_sound_is_playing)
				{
					context.audioManager->stopSound(this->channel);
					this->channel = 0;
					this->health_sound_is_playing = false;
				}

				if (healthComponent->currentHealth <= 30 && !health_sound_is_playing) {
					this->channel = context.audioManager->playSound("Heartbeat", 0, -1);
					this->health_sound_is_playing = true;
				}
				if (healthComponent->currentHealth <= 0) {
					context.audioManager->stopSound();

					auto endState = context.stateMachine->getState<EndState>();

					int totalScore;
					int time;
					int kills;
					int red;
					int blue;
					int green;

					for (const auto& entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
						totalScore = entityManager->getComponent<ScoreComponent>(entity.id)->totalScore;

						auto scoreComponent = entityManager->getComponent<ScoreComponent>(entity.id);
						scoreComponent->survivedTime += context.deltaTime;

						time = scoreComponent->survivedTime;
						kills = scoreComponent->killedEnemies;
						red = scoreComponent->gatheredRedResources;
						green = scoreComponent->gatheredGreenResources;
						blue = scoreComponent->gatheredBlueResources;
					}

					//TODO: opsplitsen in een andere functie
					endState->totalscore = totalScore;
					endState->time = time;
					endState->kills = kills;
					endState->resourceRed = red;
					endState->resourceGreen = green;
					endState->resourceBlue = blue;
				
					context.stateMachine->setState<EndState>(context);
				}
			}
		}

		GameOverSystem::~GameOverSystem()
			= default;

	}
}

