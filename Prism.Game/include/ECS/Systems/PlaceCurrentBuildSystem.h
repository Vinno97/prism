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
		class PlaceCurrentBuildSystem : public System {

		public:
			PlaceCurrentBuildSystem(EntityManager &entityManager, float wallRequirements, float towerRequirements, float mineRequirements);
			~PlaceCurrentBuildSystem();
			void update(Context& context) override;

		private:
			EntityFactory ef;
			float shootDeltaTime = 0;
			float waitTime = 0.1;

			float wallRequirements;
			float towerRequirements;
			float mineRequirements;
			float buildRange = 5;
		};
	}
}