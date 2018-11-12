#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/HealthComponent.h"


namespace ECS {
	namespace Systems {
		AttackSystem::AttackSystem(std::shared_ptr<EntityManager> entityManager) : System(entityManager) {

		}

		AttackSystem::~AttackSystem() = default;

		void AttackSystem::update(Context context) {
			auto healthEntities = this->entityManager->getAllEntitiesWithComponent<BoundingBoxComponent>();


			//if (healthEntities.size() > 1) {
			//	for (size_t i = 0; i < healthEntities.size(); i++)
			//	{
			//		if (i < healthEntities.size()) {
			//			if (aabbCollider.CheckCollision(healthEntities[i].component->boundingBox, healthEntities[i + 1].component->boundingBox)) {
			//				auto currentEntity = this->entityManager->getComponent<HealthComponent>(healthEntities[i].id);
			//				currentEntity->health = -10;

			//				std::cout << currentEntity->health;
			//			}
			//		}			
			//	}
			//}
			//else {
			//	std::cout << "Er is maar een entity";
			//}
		}
	}
}

