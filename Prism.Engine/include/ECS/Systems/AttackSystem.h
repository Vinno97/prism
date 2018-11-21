#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

namespace ECS {
	namespace Systems {
		class AttackSystem : public System {
		public:
			AttackSystem(EntityManager &entityManager);
			~AttackSystem();
			void update(Context context) override;
			System* clone() override;

			///<summary>
			/// Method to update the entity when collision is detected
			///<param name="id">The ID of the Entity to update
			///</summary>
			void updateEntity(int id);
		private:
			Physics::QuadTree quadTree;
			Physics::AABBCollider aabbCollider;
		};
	}
}

