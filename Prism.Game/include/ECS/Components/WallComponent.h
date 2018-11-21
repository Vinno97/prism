#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct WallComponent : Component {
			Component* Clone() override {
				return new WallComponent();
			}
		};
	}
}