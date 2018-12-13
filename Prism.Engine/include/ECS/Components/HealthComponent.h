#pragma once
#include "Component.h"

namespace ECS
{
	namespace Components
	{
		struct HealthComponent : Component
		{
			HealthComponent() = default;

			//The current health of this entity
			float currentHealth{0};

			//the Maximum health of this entity
			float maxHealth{0};

			HealthComponent(float maxHealth) : currentHealth(maxHealth), maxHealth(maxHealth)
			{
			};

			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<HealthComponent>();
				component->currentHealth = currentHealth;
				component->maxHealth = maxHealth;
				return component;
			}
		};
	}
}
