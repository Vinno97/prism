#pragma once

#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"

namespace ECS {
	namespace Systems {
		class TowerAimingSystem : public System
		{
		public:
			TowerAimingSystem(EntityManager& entityManager);
			~TowerAimingSystem() = default;

			void update(Context& context) override;
			//System* clone() override;
		private:
			const float radius = 5;
			bool enemyIsInRange(ECS::Components::PositionComponent & playerPosition, ECS::Components::PositionComponent & resourcePointPosition, float radius) const;

		};
	}
}