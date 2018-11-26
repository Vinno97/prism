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
			void update(Context& context) override;
			System* clone() override;
		private:
			Physics::AABBCollider aabbCollider;

			/// <summary>
			/// this method returns the amount of collisions there are with a given boundingbox;
			/// </sumaary>
			int CountCollisions(Physics::BoundingBox &box1, Physics::BoundingBox &adress, std::vector<const Physics::BoundingBox *> &vector);
		};
	}
}


	
