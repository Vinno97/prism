#pragma once

#include "World/Assemblers/EntityAssembler.h"
#include "EntityFactory.h"
#include "ECS/EntityManager.h"

namespace World
{
	namespace Assemblers
	{
		class PrismEntityAssembler : public EntityAssembler
		{
		public:
			PrismEntityAssembler();
			//PrismEntityAssembler(ECS::EntityManager& entityManager, EntityFactory& factory_);
		private:
			//EntityFactory factory;
		};
	}
}
