#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"
#include "ECS/Components/InventoryComponent.h"

namespace ECS {
	namespace Systems {
		class ResourceGatherSystem : public System
		{
		public:
			ResourceGatherSystem(EntityManager &entityManager);
			~ResourceGatherSystem();
			void update(Context& context) override;
			System* clone() override;
		private:
			int xMargin = 1;
			int yMargin = 1;
			bool shouldIncreaseResources(PositionComponent& playerPosition, PositionComponent& resourcePointPosition);
			void increateResource(std::string resourceType, InventoryComponent& playerInventory, float gatherRate);
		};
	}
}