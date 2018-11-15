#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

namespace ECS {
	namespace Systems {
		class BumpSystem : public System {
		public:
			BumpSystem(ECS::EntityManager &entityManager);
			~BumpSystem();
			void update(Context context) override;
			System* clone() override;
		private:
			Physics::AABBCollider aabbCollider;
		};
	}
}


	
