#pragma once

#include <EntityFactory.h>
#include "Context.h"
#include "ECS/Systems/System.h"
#include "InputManager.h"

namespace ECS {
	namespace Systems {
		class EnemySpawnSystem : public System
		{
		public:
			explicit EnemySpawnSystem(EntityManager &entityManager);
			~EnemySpawnSystem() override;
			void update(Context& context) override;
		private:
			EntityFactory entityFactory;
		};
	}
}