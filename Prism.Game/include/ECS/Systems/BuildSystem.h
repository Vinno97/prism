#pragma once
#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"
#include "EntityFactory.h"
#include "Math/Vector3f.h"

namespace ECS {
	namespace Systems {
		class BuildSystem : public System {
		public:
			BuildSystem(EntityManager &entityManager);
			~BuildSystem();
			void update(Context& context) override;

		private:
			bool isBuilding = false;
			int buildingId = -1;
			EntityFactory ef;
			float deltaTime;
			float pressTime = 0.5;
			Math::Vector3f buildingColor;
			float wallRequirements = 50;
			float towerRequirements = 50;
			float factoryRequirements = 50;
		};
	}
}