#pragma once

#include "World/Assemblers/BaseAssembler.h"

namespace World
{
	namespace Assemblers
	{
		class TowerAssembler : public BaseAssembler
		{
		public:
			void assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const override;
			void disassemble(int entity, WorldObject& worldObject,
			                 const ECS::EntityManager& entityManager) const override;
		};
	}
}
