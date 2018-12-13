#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "InputManager.h"

namespace ECS
{
	namespace Systems
	{
		class EnemySpawnSystem : public System
		{
		public:
			EnemySpawnSystem(EntityManager& entityManager);
			~EnemySpawnSystem();
			void update(Context& context) override;
		};
	}
}
