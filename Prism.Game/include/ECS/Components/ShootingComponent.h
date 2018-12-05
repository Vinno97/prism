#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ShootingComponent : Component {
			float xdirection;
			float ydirection;
			bool isShooting;

			std::unique_ptr<Component> clone() override {
				return std::make_unique<ShootingComponent>();
			}
		};
	}
}
