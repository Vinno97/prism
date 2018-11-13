#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct InventoryComponent : Component {

			int redResource = 0;
			int greenResource = 0;
			int blueResource = 0;
			Component* Clone() override {
				return new InventoryComponent();
			}
		};
	}
}
