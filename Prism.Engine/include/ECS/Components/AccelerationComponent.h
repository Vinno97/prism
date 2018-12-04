#pragma once

#include "Component.h"

namespace ECS
{
	namespace Components
	{
		struct AccelerationComponent : Component
		{
			AccelerationComponent() = default;

			explicit AccelerationComponent(int force_) : force(force_)
			{
			};
			/// <summary>
			///	The amount of acceleration in units/second^2
			/// </summary>
			double force{1};

			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<AccelerationComponent>();
				component->force = force;
				return component;
			}
		};
	}
}
