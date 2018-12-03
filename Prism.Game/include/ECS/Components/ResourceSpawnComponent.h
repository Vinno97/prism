#pragma once

#include "ECS/Components/Component.h"
#include "Enums/ResourceTypeEnum.h"
namespace ECS {
	namespace Components {
		struct ResourceSpawnComponent : Component {

			ResourceSpawnComponent() = default;
			ResourceSpawnComponent(float gatherRate_, Enums::ResourceType type_, float value_) :
				SpawnTimer(gatherRate_), resourceType(type_), value(value_) {};

			const Enums::ResourceType resourceType{};
			float SpawnTimer = 1;
			const float value = 1;

			std::unique_ptr<Component> clone() override {
				return std::make_unique<ResourceSpawnComponent>(SpawnTimer, resourceType, value);
			}
		};
	}
}
