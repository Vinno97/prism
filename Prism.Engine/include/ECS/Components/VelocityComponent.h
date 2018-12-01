#pragma once

#include "Component.h"

namespace ECS
{
	namespace Components
	{
		struct VelocityComponent : Component
		{
			VelocityComponent() = default;

			VelocityComponent(double dx_, double dy_) : dx(dx_), dy(dy_)
			{
			};

			/// <summary>
			///	The amount of delta X in units/second
			/// </summary>
			double dx{0};

			/// <summary>
			///	The amount of delta Y in units/second
			/// </summary>
			double dy{0};

			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<VelocityComponent>();
				component->dx = dx;
				component->dy = dy;
				return component;
			}
		};
	}
}
