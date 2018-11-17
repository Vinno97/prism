#pragma once

#include "World/Assemblers/BaseAssembler.h"

namespace World {
	namespace Assemblers {
		class AppearanceAssembler : public BaseAssembler {
		public:
			virtual void assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const;
			virtual void disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const;
		};
	}
}
