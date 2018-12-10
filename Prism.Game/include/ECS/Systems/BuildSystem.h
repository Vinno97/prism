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
			BuildSystem(EntityManager &entityManager, float wallRequirements, float towerRequirements, float mineRequirements);
			~BuildSystem();
			void update(Context& context) override;

		private:
			/// <summary>
			/// Decides what needs to be build based on user input
			/// </summary>
			int setCurrentBuild(Context &context);
			
			/// <summary>
			/// Places a building if the requirements are met
			/// </summary>
			void placeCurrentBuild(Context &context, unsigned int playerId);

			/// <summary>
			/// Moves the building based on mouse movement
			/// </summary>
			void moveCurrentBuilt();

			int buildingId = -1;
			BuildingType currentBuild = BuildingType::NONE;

			EntityFactory ef;
			float deltaTime;
			float waitTime = 0.5;
			
			Math::Vector3f buildingColor;
			float buildingScaleX;
			float buildingScaleY;
			float buildingScaleZ;
			float posX = 0;
			float posY = 0;

			float wallRequirements;
			float towerRequirements;
			float mineRequirements;
		};
	}
}