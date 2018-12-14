#pragma once
#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"
#include "Math/Vector3f.h"
#include "ECS/Components/AppearanceComponent.h"

namespace ECS {
	namespace Systems {
		class PlaceCurrentBuildSystem : public System {

		public:
			PlaceCurrentBuildSystem(EntityManager &entityManager, float wallRequirements, float towerRequirements, float mineRequirements , float buildRange);
			~PlaceCurrentBuildSystem();
			void update(Context& context) override;
			
		private:
			Math::Vector3f canBuildColor = Math::Vector3f{ 0.5f, 1.0f, 1.0f };
			Math::Vector3f CanNotBuildColor = Math::Vector3f{ 1.0f, 0.5f, 0.5f };
			Math::Vector3f CanRemoveBuildColor = Math::Vector3f{ 0.5f, 1.0f, 0.5f };

			float wallRequirements;
			float towerRequirements;
			float mineRequirements;
			float buildRange;
			bool isBuilding(unsigned int id) const;
		};
	}
}