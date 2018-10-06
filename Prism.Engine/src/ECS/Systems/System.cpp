#include "ECS/Systems/System.h"
#include "ECS/EntityManager.h"
#include "Context.h"


namespace ECS {
	namespace Systems {
		System::System(EntityManager* entityManager) {
			this->entityManager = entityManager;
		}

		System::~System()
			= default;
	}
}