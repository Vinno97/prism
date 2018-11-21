#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct MineComponent : Component {
			Component* Clone() override {
				return new MineComponent();
			}
		};
	}
}