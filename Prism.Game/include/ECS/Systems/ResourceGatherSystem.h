#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"


namespace ECS {
	namespace Systems {
		class ResourceGatherSystem : public System
		{
		public:
			ResourceGatherSystem(EntityManager &entityManager);
			~ResourceGatherSystem();
			void update(Context context) override;
			System* clone() override;
		private:
			int xMargin = 5;
			int yMargin = 5;
			bool shouldIncreaseResources(PositionComponent& playerPosition, PositionComponent& resourcePointPosition);
		};
	}
}