#pragma once
#include "Component.h"

namespace ECS
{
	namespace Components
	{
		struct HealthComponent : Component
		{
			HealthComponent() = default;

			/// <summary>
			///	The position in units
			/// </summary>
			int health{0};

			HealthComponent(int healthIn) : health(healthIn)
			{
			};

			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<HealthComponent>();
				component->health = health;
				return component;
			}
		};
	}
}
