#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

namespace ECS
{
	namespace Systems
	{
		class CheatSystem : public System
		{
		public:
			CheatSystem(EntityManager& entityManager);
			~CheatSystem();
			void update(Context& context) override;
			float ticks = 0;
			void increaseHealth();
			void increaseResources();
			void decreaseHealth();
			void decreaseResources();
			void increaseGameSpeed();
			void decreaseGameSpeed();
			void resetGameSpeed();
		private:
			float multiplier = 1;
		};
	}
}
