#include "ECS/Systems/RestockResourceSystem.h"

#include "Context.h"


namespace ECS {
	namespace Systems {
		RestockResourceSystem::RestockResourceSystem(std::shared_ptr<EntityManager> entityManager) : System(entityManager) {
		}

		RestockResourceSystem::~RestockResourceSystem()
			= default;

		void RestockResourceSystem::update(Context context) {

		}
	}
}
