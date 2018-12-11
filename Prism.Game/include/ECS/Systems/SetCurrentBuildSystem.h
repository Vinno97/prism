#pragma once
#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"
#include "EntityFactory.h"
#include "Math/Vector3f.h"
#include "ECS/Components/AppearanceComponent.h"

namespace ECS {
	namespace Systems {
		class SetCurrentBuildSystem : public System {

		public:
			SetCurrentBuildSystem(EntityManager &entityManager);
			~SetCurrentBuildSystem();
			void update(Context& context) override;

		private:
			EntityFactory ef;
			float buildWaitTime = 0;
			float shootWaitTime = 0;
			float waitTime = 0.1;
		};
	}
}