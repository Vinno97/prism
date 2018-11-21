#pragma once

#include "World/Assemblers/BaseAssembler.h"
#include "Enums/ResourceTypeEnum.h"

namespace World {
	namespace Assemblers {
		class ResourceSpawnAssembler : public BaseAssembler {
		public:
			ResourceSpawnAssembler();
			void assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const;
			void disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const;
		private:
			std::map<int, Enums::ResourceType> resourceTypes;
		};
	}
}
