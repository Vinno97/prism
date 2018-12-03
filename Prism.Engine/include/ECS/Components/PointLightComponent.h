#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct PointLightComponent : Component {

			Math::Vector3f color; 
			Math::Vector3f position; 
				
			Component* Clone() override {
				return new PointLightComponent();
			}
		};
	}
}