#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ResourceSpawnComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "EntityFactory.h"
#include "Enums/ResourceTypeEnum.h"
namespace ECS {
	namespace Systems {
		class ResourceGatherSystem : public System
		{
		public:
			ResourceGatherSystem(EntityManager &entityManager);
			~ResourceGatherSystem() = default;
			void update(Context& context) override;
			System* clone() override;
		private:
			
			EntityFactory entityFactory;
			/// <summary>
			/// Checks if an entity with the resourceGatherComponent is in range to collect the resource
			/// </summay>
			bool shouldIncreaseResources(PositionComponent& playerPosition, PositionComponent& resourcePointPosition, float radius);
			void CreateBlob(int resourcePointID, Enums::ResourceType resourceType, float value);
		};
	}
}