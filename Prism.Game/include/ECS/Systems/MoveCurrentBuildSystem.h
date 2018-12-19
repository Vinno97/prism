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
		class MoveCurrentBuildSystem : public System {

		public:
			MoveCurrentBuildSystem(EntityManager &entityManager);
			~MoveCurrentBuildSystem();
			void update(Context& context) override;
		};
	}
}