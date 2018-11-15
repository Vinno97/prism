#include "ECS/Systems/MousePointSystem.h"

#include "Context.h"


namespace ECS {
	namespace Systems {
		MousePointSystem::MousePointSystem(EntityManager& entityManager) : System(entityManager) {
		}

		MousePointSystem::~MousePointSystem()
			= default;

		void MousePointSystem::update(Context context) {

		}

		System * MousePointSystem::clone()
		{
			return new MousePointSystem(*entityManager);
		}
	}
}
