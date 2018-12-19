#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct EnemySpawnComponent : Component {
			EnemySpawnComponent() = default;
			EnemySpawnComponent(float interval, float timeSinceLastSpawn, bool enabled) : spawnInterval( interval ), timeSinceLastSpawn( timeSinceLastSpawn ), enabled( enabled ) {};

			float spawnInterval = 10; // Spawn a new enemy when this time has passed (in seconds)
			float timeSinceLastSpawn = 0;
			bool enabled = true;

			std::unique_ptr<Component> clone() override {
				return std::make_unique<EnemySpawnComponent>( spawnInterval, timeSinceLastSpawn, enabled );
			}
		};
	}
}
