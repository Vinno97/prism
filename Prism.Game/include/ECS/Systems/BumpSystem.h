#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

namespace ECS {
	namespace Systems {
		class BumpSystem : public System {
		public:
			enum CollisionAxis {
				X,
				Y,
				BOTH
			};
			BumpSystem(ECS::EntityManager &entityManager);
			~BumpSystem();
			void update(Context& context) override;
		private:
			Physics::AABBCollider aabbCollider;

			/// <summary>
			/// this method returns the amount of collisions there are with a given boundingbox;
			/// </sumaary>
			int CountCollisions(Physics::BoundingBox &currentBox, std::vector<unsigned int> &vector);
			
			/// <summary>
			/// this method returns the Axis on wich the colliderBox collides with other;
			/// </sumaary>
			ECS::Systems::BumpSystem::CollisionAxis GetCollisionAxis(Physics::BoundingBox &colliderBox , Physics::BoundingBox &other);
		};
	}
}


	
