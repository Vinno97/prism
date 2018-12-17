#include "ECS/Systems/ScoreSystem.h"
#include "StateMachine.h"
#include "States/PrismGame.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ScoreComponent.h"
#include "EntityFactory.h"


namespace ECS {
	namespace Systems {
		using namespace Components;
		using namespace States;
		ScoreSystem::ScoreSystem(EntityManager& entityManager) : System(entityManager)
		{
		}

		ScoreSystem::~ScoreSystem()
			= default;

		void ScoreSystem::update(Context& context)
		{
			auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
			auto score = entityManager->getComponent<ScoreComponent>(player.id);

			bool nightmare = false;
			if (context.stateMachine->hasState<PrismGame>()) {
				nightmare = context.stateMachine->getState<PrismGame>()->isNightmare();
			}
		
			score->totalScore = floor((score->killedEnemies * 503) + ((score->gatheredBlueResources + score->gatheredGreenResources + score->gatheredRedResources) * 6.6) + (log2(score->survivedTime + 1) * 5)) * (1 + nightmare);

		}
	}
}
