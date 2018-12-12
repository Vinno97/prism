#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "Enums/ResourceTypeEnum.h"

namespace ECS {
	namespace Systems {
		using namespace Components;

		class ResourceBlobSystem : public System
		{
		public:
			ResourceBlobSystem(EntityManager &entityManager);
			~ResourceBlobSystem() = default;
			void update(Context& context) override;
		private:
			void removeResourceBlobs(PositionComponent & playerPosition, PositionComponent & blobPosition, int blob, Context & context);
			void increateResource(Enums::ResourceType resourceType, InventoryComponent & playerInventory, float gatherRate);

		};
	}
}
