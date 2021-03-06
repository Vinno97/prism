#pragma once

#include "ECS/Components/Component.h"
#include "Enums/ResourceTypeEnum.h"

namespace ECS {
	namespace Components {
		struct ResourceBlobComponent : Component {
			

			ResourceBlobComponent() = default;
			ResourceBlobComponent(float value_, Enums::ResourceType type_) :
				value(value_), resourceType(type_) {};

			const Enums::ResourceType resourceType{};
			const float value = 1;

			std::unique_ptr<Component> clone() override {
				return std::make_unique<ResourceBlobComponent>(value, resourceType);
			}
		};
	}
}
