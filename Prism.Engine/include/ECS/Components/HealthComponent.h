#pragma once
#include "Component.h"

namespace ECS {
	namespace Components {
		struct HealthComponent : Component {
			HealthComponent() = default;

			/// <summary>
			///	The position in units
			/// </summary>
			int health;
			HealthComponent(int healthIn) : health(healthIn) {};
			Component* Clone() override {
				HealthComponent* component = new HealthComponent();
				component->health = health;
				return component;
			}
		};
	}
}