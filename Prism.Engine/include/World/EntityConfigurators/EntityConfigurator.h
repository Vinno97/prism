#pragma once

#include "World/WorldObject.h"
#include "ECS/EntityManager.h"

namespace World
{
	namespace EntityConfigurators
	{
		class EntityConfigurator
		{
		public:
			virtual void configure(int entity, const WorldObject& object, ECS::EntityManager& entityManager) const = 0;
		};
	}
}
