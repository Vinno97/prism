#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "EntityFactory.h"
#include "Enums/ResourceTypeEnum.h"

namespace ECS {
	namespace Systems {
		using namespace Components;

		class ResourceGatherSystem : public System
		{
		public:
			ResourceGatherSystem(EntityManager &entityManager);
			~ResourceGatherSystem() = default;
			void update(Context& context) override;
		private:
			
			EntityFactory entityFactory;
			/// <summary>
			/// Checks if an entity with the resourceGatherComponent is in range to collect the resource
			/// </summay>
			bool shouldIncreaseResources(PositionComponent& playerPosition, PositionComponent& resourcePointPosition, float radius) const;
			void createResourceBlob(int resourcePointID, Enums::ResourceType resourceType, float value);
		};
	}
}
