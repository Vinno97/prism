#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"

namespace ECS {
	namespace Systems {
		class EnemyPathFindingSystem : public System
		{
		public:
			EnemyPathFindingSystem(EntityManager &entityManager, float enemySpeed);
			~EnemyPathFindingSystem();
			void update(Context& context) override;
		private:
			float enemySpeed;
		};
	}
}