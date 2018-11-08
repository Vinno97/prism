#include "ECS/Systems/RestockResourceSystem.h"

#include "Context.h"


namespace ECS {
	namespace Systems {
		RestockResourceSystem::RestockResourceSystem(EntityManager& entityManager) : System(entityManager) {
		}

		RestockResourceSystem::~RestockResourceSystem()
			= default;

		void RestockResourceSystem::update(Context context) {

		}
		System * RestockResourceSystem::clone()
		{
			return new RestockResourceSystem(*entityManager);
		}
	}
}
