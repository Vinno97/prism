#pragma once

#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class TowerAimingSystem : public System
		{
		public:
			TowerAimingSystem(EntityManager& entityManager);
			~TowerAimingSystem() = default;

			void update(Context& context) override;
			System* clone() override;
		private:
			const float radius = 5;
			bool enemyIsInRange(PositionComponent & playerPosition, PositionComponent & resourcePointPosition, float radius) const;

		};
	}
}