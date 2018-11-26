#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

namespace ECS {
	namespace Systems {
		class CheatSystem : public System {
		public:
			CheatSystem(EntityManager &entityManager);
			~CheatSystem();

			void update(Context& context) override;
			System* clone() override;
			float ticks = 0;
			void increaseHealth();
		};
	}
}

