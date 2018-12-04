#include <cmath>

#include "ECS/Systems/PathFindingSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/TargetComponent.h"
#include "ECS/Components/AccelerationComponent.h"
#include "Math/Vector3.h"

namespace ECS {
	namespace Systems {
		using namespace Components;

		PathFindingSystem::PathFindingSystem(ECS::EntityManager &entityManager) : System(entityManager) {}

		PathFindingSystem::~PathFindingSystem() = default;

		void PathFindingSystem::update(Context &context) {
			for (const auto &subject: entityManager->getAllEntitiesWithComponent<TargetComponent>()) {
				const auto subjectPosition = entityManager->getComponent<PositionComponent>(subject.id);
				const auto subjectVelocity = entityManager->getComponent<VelocityComponent>(subject.id);
				const auto subjectAcceleration = entityManager->getComponent<AccelerationComponent>(subject.id);

				const auto targetPosition = entityManager->getComponent<PositionComponent>(subject.component->target);

				if (subjectPosition != nullptr && subjectVelocity != nullptr && targetPosition != nullptr) {
					auto acceleration{subjectAcceleration != nullptr ? subjectAcceleration->force : 1};

					auto vector = Math::Vector2d(targetPosition->x - subjectPosition->x,
					                             targetPosition->y - subjectPosition->y);

					vector.normalize();
					subjectVelocity->dx += acceleration * vector.x * context.deltaTime;
					subjectVelocity->dy += acceleration * vector.y * context.deltaTime;
				}
			}
		}
	}
}
