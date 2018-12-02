#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct CliffCornerComponent : Component {
			Component* Clone() override {
				return new CliffCornerComponent();
			}
		};
	}
}