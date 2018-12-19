#pragma once

#include "World/WorldObject.h"
#include "ECS/EntityManager.h"

namespace World {
	namespace Assemblers {
		class BaseAssembler {
		public:
			virtual ~BaseAssembler() = default;
			BaseAssembler() = default;

			virtual void assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const = 0;
			virtual void disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const = 0;
		};
	}
}
