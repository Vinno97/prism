#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct BuildComponent : Component {
			bool isBuilding = false;
			std::unique_ptr<Component> clone() override {
				BuildComponent component;
				component.isBuilding = this->isBuilding;
				return std::make_unique<BuildComponent>(component);
			}
		};
	}
}
