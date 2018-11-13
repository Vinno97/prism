#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

namespace ECS {
	namespace Systems {
		class CollisionHandlerSystem : public System {
		public:
			CollisionHandlerSystem(ECS::EntityManager &entityManager);
			~CollisionHandlerSystem();
			void update(Context context) override;
			System* clone() override;
		private:
			Physics::AABBCollider aabbCollider;
			int AmountCollisions(Physics::BoundingBox &box1, Physics::BoundingBox &adress,std::vector<const Physics::BoundingBox *> &vector);
		};
	}
}


	
