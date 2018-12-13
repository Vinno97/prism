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
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"

namespace ECS
{
	namespace Systems
	{
		using namespace Components;
		using namespace States;

		GameOverSystem::GameOverSystem(EntityManager& entityManager) : System(entityManager)
		{
		}

		void GameOverSystem::update(Context& context)
		{
			for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>())
			{
				auto healthComponent = entityManager->getComponent<HealthComponent>(entity.id);
				if (healthComponent->currentHealth <= 30 && !health_sound_is_playing)
				{
					context.audioManager->playSound("Heartbeat", -1);
					this->health_sound_is_playing = true;
				}
				if (healthComponent->currentHealth <= 0)
				{
					context.audioManager->stopSound();
					context.stateMachine->setState<EndState>(context);
				}
			}
		}

		GameOverSystem::~GameOverSystem()
		= default;
	}
}
