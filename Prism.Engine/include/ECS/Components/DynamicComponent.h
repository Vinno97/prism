#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct DynamicComponent : Component {
			float lifeTime{0};

			std::unique_ptr<Component> clone() override {
				return std::make_unique<DynamicComponent>();
			}
		};
	}
}
