#pragma once

#include "Component.h"

namespace ECS
{
	namespace Components
	{
		struct DragComponent : Component
		{
			DragComponent() = default;

			DragComponent(int force_) : force(force_)
			{
			};
			/// <summary>
			///	The amount of drag in units/second^2
			/// </summary>
			double force{0};

			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<DragComponent>();
				component->force = force;
				return component;
			}
		};
	}
}
