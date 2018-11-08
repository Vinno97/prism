#pragma once

#include "World/EntityAssembler.h"
#include "EntityFactory.h"
#include "ECS/EntityManager.h"

namespace World {
	class PrismEntityAssembler : public EntityAssembler {
	public:
		PrismEntityAssembler(ECS::EntityManager& entityManager, EntityFactory& factory_);
	private:
		EntityFactory factory;
	};
}
