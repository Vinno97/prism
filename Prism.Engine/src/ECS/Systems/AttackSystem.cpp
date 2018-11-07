#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/HealthComponent.h"

namespace ECS {
	namespace Systems {
		AttackSystem::AttackSystem(std::shared_ptr<EntityManager> entityManager) : System(entityManager) {

		}

		AttackSystem::~AttackSystem() = default;

		void AttackSystem::update(Context context) {

		}
	}
}

