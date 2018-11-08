#include "World/EntityConfigurators/PositionConfigurator.h"

#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace ECS::Components;

namespace World {
	namespace EntityConfigurators {
		void PositionConfigurator::configure(int entity, WorldObject &object, EntityManager& entityManager) {
			if (entityManager.hasComponent<PositionComponent>(entity)) {
				auto position = entityManager.getComponent<PositionComponent>(entity);
				position->x = object.x;
				position->y = object.x;
			}
		}
	}
}