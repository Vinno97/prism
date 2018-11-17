#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"


namespace ECS {
	namespace Systems {
		class ResourceBlobSystem : public System
		{
		public:
			ResourceBlobSystem(EntityManager &entityManager);
			~ResourceBlobSystem();
			void update(Context& context) override;
			void RemoveBlobs(PositionComponent & playerPosition, PositionComponent & blobPosition, int blob);
			System* clone() override;

		};
	}
}