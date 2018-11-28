#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ShootingComponent : Component {
			float xdirection;
			float ydirection;
			bool isShooting;
			float pastTime = 0;
			float cooldown = 0.2;

			Component* Clone() override {
				return new ShootingComponent();
			}
		};
	}
}