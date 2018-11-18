#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/InventoryComponent.h"
#include "Enums/ResourceTypeEnum.h"

namespace ECS {
	namespace Systems {
		class ResourceBlobSystem : public System
		{
		public:
			ResourceBlobSystem(EntityManager &entityManager);
			~ResourceBlobSystem() = default;
			void update(Context& context) override;
			void RemoveBlobs(PositionComponent & playerPosition, PositionComponent & blobPosition, int blob);
			void increateResource(Enums::ResourceType resourceType, InventoryComponent & playerInventory, float gatherRate);
			System* clone() override;

		};
	}
}