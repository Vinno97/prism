#include "World/EntityConfigurators/AppearanceConfigurator.h"

#include "ECS/Components/AppearanceComponent.h"

using namespace ECS;
using namespace ECS::Components;

namespace World {
	namespace EntityConfigurators {
		void AppearanceConfigurator::configure(int entity, const WorldObject &object, EntityManager& entityManager) const {
			if (entityManager.hasComponent<AppearanceComponent>(entity)) {
				auto appearance = entityManager.getComponent<AppearanceComponent>(entity);
				appearance->scaleX *= object.width;
				appearance->scaleY *= (object.width + object.height) / 2.f;
				appearance->scaleZ *= object.height;
			}
		}
	}
}