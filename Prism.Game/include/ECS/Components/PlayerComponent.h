#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct PlayerComponent : Component {
			Component* Clone() override {
				return new PlayerComponent();
			}
		};
	}
}