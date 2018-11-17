#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ResourceBlobComponent : Component {

			ResourceBlobComponent() = default;
			ResourceBlobComponent(float value_, std::string type_) :
				value(value_), resourceType(type_) {};

			std::string resourceType{};
			float value = 1;

			Component* Clone() override {
				return new ResourceBlobComponent(value, resourceType);
			}
		};
	}
}