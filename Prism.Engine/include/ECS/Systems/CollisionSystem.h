#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"
#include <map>

namespace ECS {
	namespace Systems {
		class CollisionSystem : public System {
		public:
			CollisionSystem(ECS::EntityManager &entityManager, float width, float height, float posX, float posY,unsigned int maxObjects);
			~CollisionSystem();
			void update(Context& context) override;
			System* clone() override;
		private:
			std::map<const Physics::BoundingBox *,unsigned int> boundingBoxMap;
			Physics::QuadTree quadTree;
			Physics::AABBCollider aabbCollider;
		};
	}
}


	
