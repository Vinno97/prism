#pragma once


namespace ECS {
	namespace Components {
		struct ScoreComponent : Component {
			ScoreComponent() = default;

			int killedEnemies = 0;
			int gatheredRedResources = 0;
			int gatheredGreenResources = 0;
			int gatheredBlueResources = 0;
			int survivedTime = 0;

			Component* Clone() override {
				auto component = new ScoreComponent();
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