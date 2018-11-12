#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Components/HealthComponent.h"


namespace ECS {
	namespace Systems {
		AttackSystem::AttackSystem(std::shared_ptr<EntityManager> entityManager) : System(entityManager) {

		}

		AttackSystem::~AttackSystem() = default;

		void AttackSystem::update(Context context) {
			auto healthEntities = this->entityManager->getAllEntitiesWithComponent<HealthComponent>();

			//while (appearanceEntities[0].component->health > 0) {
			//	cout << appearanceEntities[0].component->health << endl;

			//	appearanceEntities[0].component->health = appearanceEntities[0].component->health - 10;
			//}				


		}
	}
}

