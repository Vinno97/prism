#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

namespace ECS {
	namespace Systems {
		class CollisionSystem : public System {
		public:
			CollisionSystem(ECS::EntityManager &entityManager, float width, float height, float posX, float posY,unsigned int maxObjects);
			~CollisionSystem();
			void update(Context context) override;
			System* clone() override;
		private:
			Physics::QuadTree quadTree;
			Physics::AABBCollider aabbCollider;
			int AmountCollisions(Physics::BoundingBox &box1, Physics::BoundingBox &adress,std::vector<const Physics::BoundingBox *> &vector);
		};
	}
}


	
