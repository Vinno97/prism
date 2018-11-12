#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct EnemySpawnComponent : Component {
			EnemySpawnComponent() = default;
			EnemySpawnComponent(int interval) : spawnInterval{ interval } {};

			int spawnInterval = 0; // Spawn a new enemy when this time has passed (in seconds)

			Component* Clone() override {
				return new EnemySpawnComponent{ spawnInterval };
			}
		};
	}
}