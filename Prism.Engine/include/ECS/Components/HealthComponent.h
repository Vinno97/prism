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
			float ticks = 0;

			void increase() {
				if (ticks == 0)
				{
					ticks = 1;;
					health += 100;
					std::cout << health << std::endl;
				}

				if (ticks > 0) {
					ticks++;
				}

				if (ticks == 8) {
					ticks = 0;
				}
			}

			Component* Clone() override {
				HealthComponent* component = new HealthComponent();
				component->health = health;
				return component;
			}
		};
	}
}