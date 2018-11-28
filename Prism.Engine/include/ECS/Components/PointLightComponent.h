#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct PointLightComponent : Component {
			Component* Clone() override {
				return new PointLightComponent();
			}
		};
	}
}