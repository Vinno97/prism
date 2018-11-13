#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ResourceSpawnComponent : Component {
			ResourceSpawnComponent() = default;
			ResourceSpawnComponent(int gatherRate_, std::string type_) : 
				gatherRate(gatherRate_), resourceType(type_){};

			std::string resourceType{};

			int gatherRate = 0;
			Component* Clone() override {
				return new ResourceSpawnComponent(gatherRate, resourceType);
			}
		};
	}
}