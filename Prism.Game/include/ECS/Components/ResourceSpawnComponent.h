#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ResourceSpawnComponent : Component {

			ResourceSpawnComponent() = default;
			ResourceSpawnComponent(float gatherRate_, std::string type_, float value_) :
				SpawnTimer(gatherRate_), resourceType(type_), value(value_) {};

			std::string resourceType{};
			float SpawnTimer = 1;
			float value = 1;

			Component* Clone() override {
				return new ResourceSpawnComponent(SpawnTimer, resourceType, value);
			}
		};
	}
}