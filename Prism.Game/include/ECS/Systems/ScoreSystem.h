#pragma once
#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

namespace ECS {
	namespace Systems {

		class ScoreSystem : public System {
		public:
			ScoreSystem(EntityManager &entityManager);
			~ScoreSystem();
			void update(Context& context) override;

		private:

		};
	}
}

