#pragma once
#include "Component.h"

namespace ECS {
	namespace Components {
		struct HealthComponent : Component {
			HealthComponent() = default;

			/// <summary>
			///	The position in units
			/// </summary>
			float health{0};

			HealthComponent(int healthIn) : health(healthIn) {};
			Component* Clone() override {
				auto component = new HealthComponent();
				component->health = health;
				return component;
			}
		};
	}
}