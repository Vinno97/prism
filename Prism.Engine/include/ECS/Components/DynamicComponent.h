#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct DynamicComponent : Component {
			float lifeTime;

			Component* Clone() override {
				return new DynamicComponent();
			}
		};
	}
}