#pragma once

#include "World/WorldObject.h"
#include "ECS/EntityManager.h"

namespace World {
	namespace EntityConfigurators {
		class EntityConfigurator {
		public:
			virtual void configure(int entity, WorldObject &object, ECS::EntityManager &entityManager) = 0;
		};
	}
}
