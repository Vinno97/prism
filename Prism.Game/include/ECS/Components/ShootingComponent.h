#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ShootingComponent : Component {
			int xdirection;
			int ydirection;
			bool isShooting;

			Component* Clone() override {
				return new ShootingComponent();
			}
		};
	}
}