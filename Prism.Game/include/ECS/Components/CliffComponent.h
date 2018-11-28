#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct CliffComponent : Component {
			Component* Clone() override {
				return new CliffComponent();
			}
		};
	}
}