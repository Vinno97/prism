#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ResourceSpawnComponent : Component {
			ResourceSpawnComponent() = default;
			ResourceSpawnComponent(float gatherRate_, std::string type_) : 
				gatherRate(gatherRate_), resourceType(type_){};

			std::string resourceType{};
			float gatherRate = 0;
			float SpawnTimer = 1;

			Component* Clone() override {
				return new ResourceSpawnComponent(gatherRate, resourceType);
			}
		};
	}
}