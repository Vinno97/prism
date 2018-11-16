#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Physics;

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
			QuadTree quadTree;
			AABBCollider aabbCollider;
		};
	}
}

