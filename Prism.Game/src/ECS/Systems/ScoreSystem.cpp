#include "ECS/Systems/ScoreSystem.h"
#include "EntityFactory.h"


namespace ECS {
	namespace Systems {
		ScoreSystem::ScoreSystem(EntityManager& entityManager) : System(entityManager)
		{
		}


		ScoreSystem::~ScoreSystem()
			= default;

		void ScoreSystem::update(Context& context)
		{

		}
	}
}