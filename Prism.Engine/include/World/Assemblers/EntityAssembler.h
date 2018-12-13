#pragma once

#include <map>
#include <vector>
#include <memory>
#include "World/WorldObject.h"
#include "World/Assemblers/BaseAssembler.h"

namespace World
{
	namespace Assemblers
	{
		class EntityAssembler : public BaseAssembler
		{
		public:
			EntityAssembler();

			const int PRIORITY_HIGH = 1;
			const int PRIORITY_NORMAL = 5;
			const int PRIORITY_LOW = 10;

			void addAssembler(std::unique_ptr<BaseAssembler>&& assembler);
			void addAssembler(std::unique_ptr<BaseAssembler>&& assembler, int priority);

			void assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const override;
			void disassemble(int entity, WorldObject& worldObject,
			                 const ECS::EntityManager& entityManager) const override;
		private:
			//std::vector<std::unique_ptr<BaseAssembler>> assemblers;
			std::multimap<int, std::unique_ptr<BaseAssembler>> assemblers;
		};
	}
}
