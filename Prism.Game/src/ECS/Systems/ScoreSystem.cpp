#include "ECS/Systems/ScoreSystem.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ScoreComponent.h"
#include "EntityFactory.h"


namespace ECS {
	namespace Systems {
		using namespace Components;
		ScoreSystem::ScoreSystem(EntityManager& entityManager) : System(entityManager)
		{
		}

		ScoreSystem::~ScoreSystem()
			= default;

		void ScoreSystem::update(Context& context)
		{
			auto player = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0];
			auto score = entityManager->getComponent<ScoreComponent>(player.id);

			score->totalScore = floor((score->killedEnemies * 10) + ((score->gatheredBlueResources + score->gatheredGreenResources + score->gatheredRedResources) / 3));

		}
	}
}
