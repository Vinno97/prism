#pragma once

#include "Component.h"
#include "Math/Vector3f.h"
#include "Renderer/PointLight.h"

namespace ECS {
	namespace Components {
		struct PointLightComponent : Component {

			PointLightComponent() = default;
			PointLightComponent(Math::Vector3f color_) : color{ color_ } {};

			Math::Vector3f color;
				
			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<PointLightComponent>();
				component->color = color;
				return component;
			}
		};
	}
}