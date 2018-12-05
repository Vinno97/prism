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
		class BuildSystem : public System {
		
		enum BuildingType
		{
			WALL,
			TOWER,
			MINE,	
			NONE
		};

		public:
			BuildSystem(EntityManager &entityManager);
			~BuildSystem();
			void update(Context& context) override;

		private:
			unsigned int buildEntity(BuildingType buildingType);
			int buildingId = -1;
			BuildingType currentBuild = BuildingType::NONE;

			EntityFactory ef;
			float deltaTime;
			float pressTime = 0.5;
			
			Math::Vector3f buildingColor;
			float buildingScaleX;
			float buildingScaleZ;
			bool hasDynamic = false;
			float wallRequirements = 10;
			float towerRequirements = 10;
			float factoryRequirements = 10;
		};
	}
}