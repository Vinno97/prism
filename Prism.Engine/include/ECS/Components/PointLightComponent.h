#pragma once

#include "Component.h"
#include "Renderer/PointLight.h"

namespace ECS {
	namespace Components {
		struct PointLightComponent : Component {

			Renderer::PointLight light;
				
			Component* Clone() override {
				return new PointLightComponent();
			}
		};
	}
}