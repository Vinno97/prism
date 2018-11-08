#pragma once

#include "World/EntityConfigurators/EntityConfigurator.h"

namespace World {
	namespace EntityConfigurators {
		class PositionConfigurator : EntityConfigurator {
		public:
			void configure(int entity, WorldObject &object, ECS::EntityManager &entityManager);
		};
	}
}
