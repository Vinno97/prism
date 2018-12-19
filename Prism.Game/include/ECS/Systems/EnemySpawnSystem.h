#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "InputManager.h"
#include "EntityFactory.h"

namespace ECS {
	namespace Systems {
		class EnemySpawnSystem : public System
		{
		public:
			EnemySpawnSystem(EntityManager &entityManager);
			~EnemySpawnSystem();
			void update(Context& context) override;

		private:
			float timeToNextWave = 13.f;
			float waveDuration = 0.3f;
			float currentWaveLength = 0.f;
			float timeSinceLastWave = 0.f;
			float waveNumber = 1;
			bool waveIsOngoing = false;;
		};
	}
}