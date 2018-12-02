#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct RockComponent : Component {
			Component* Clone() override {
				return new RockComponent();
			}
		};
	}
}