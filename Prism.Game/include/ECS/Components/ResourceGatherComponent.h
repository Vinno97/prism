#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ResourceGatherComponent : Component {

			ResourceGatherComponent() = default;
			ResourceGatherComponent(float range_) : gatherRange(range_) {};

			float gatherRange = 1;

			Component* Clone() override {
				auto temp = new ResourceGatherComponent();
		
				return temp;
			}
		};
	}
}
