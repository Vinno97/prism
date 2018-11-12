#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ResourceSpawnComponent : Component {
			ResourceSpawnComponent() = default;
			ResourceSpawnComponent(int maximumStock_, int currentStock_, std::string type_) : maximumStock(maximumStock_), currentStock(currentStock_), resourceType(type_){};

			std::string resourceType{};
			int maximumStock = 0;
			int currentStock = 0;
		};
	}
}