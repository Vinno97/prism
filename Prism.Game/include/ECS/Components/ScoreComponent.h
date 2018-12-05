#pragma once


namespace ECS {
	namespace Components {
		struct ScoreComponent : Component {
			ScoreComponent() = default;

			int killedEnemies = 0;
			int gatheredRedResources = 0;
			int gatheredGreenResources = 0;
			int gatheredBlueResources = 0;
			double survivedTime = 0;
			double totalScore = 0;

			std::unique_ptr<Component> clone() override {
				auto component = std::make_unique<ScoreComponent>();
				component->killedEnemies = killedEnemies;
				component->gatheredBlueResources = gatheredBlueResources;
				component->gatheredGreenResources = gatheredGreenResources;
				component->gatheredBlueResources = gatheredBlueResources;
				component->survivedTime = survivedTime;
				return component;
			}
		};
	}
}