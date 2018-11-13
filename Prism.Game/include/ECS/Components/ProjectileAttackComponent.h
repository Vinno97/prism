#pragma once

namespace ECS {
	namespace Components {
		struct ProjectileAttackComponent : Component {
			int damage;

			Component* Clone() override {
				return new ProjectileAttackComponent();
			}
		};
	}
}