#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ShootingComponent : Component {
			float xdirection;
			float ydirection;

			float zPosition;
			bool shotByTower = true;
			bool isShooting;
			float pastTime = 0;
			float cooldown = 0.1;

			std::unique_ptr<Component> clone() override {
				return std::make_unique<ShootingComponent>();
			}
		};
	}
}
