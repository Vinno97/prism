#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/InventoryComponent.h"

namespace ECS {
	namespace Systems {
		class ResourceBlobSystem : public System
		{
		public:
			ResourceBlobSystem(EntityManager &entityManager);
			~ResourceBlobSystem();
			void update(Context& context) override;
			void RemoveBlobs(PositionComponent & playerPosition, PositionComponent & blobPosition, int blob);
			void increateResource(std::string resourceType, InventoryComponent & playerInventory, float gatherRate);
			System* clone() override;

		};
	}
}