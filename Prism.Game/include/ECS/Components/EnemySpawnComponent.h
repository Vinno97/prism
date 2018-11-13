#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct EnemySpawnComponent : Component {
			EnemySpawnComponent() = default;
			EnemySpawnComponent(float interval, float timeSinceLastSpawn, bool enabled) : spawnInterval{ interval }, timeSinceLastSpawn{ timeSinceLastSpawn }, enabled{ enabled } {};

			float spawnInterval = 10; // Spawn a new enemy when this time has passed (in seconds)
			float timeSinceLastSpawn = 0;
			bool enabled = true;

			Component* Clone() override {
				return new EnemySpawnComponent{ spawnInterval, timeSinceLastSpawn, enabled };
			}
		};
	}
}