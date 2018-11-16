#pragma once
#include "Component.h"

namespace ECS {
	namespace Components {
		struct HealthComponent : Component {
			HealthComponent() = default;

			/// <summary>
			///	The position in units
			/// </summary>
			int health = 100;

			Component* Clone() override {
				HealthComponent* component = new HealthComponent();
				component->health = health;
				return component;
			}
		};
	}
}