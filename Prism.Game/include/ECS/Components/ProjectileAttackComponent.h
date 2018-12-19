#pragma once

namespace ECS {
	namespace Components {
		struct ProjectileAttackComponent : Component {
			int damage;

			std::unique_ptr<Component> clone() override {
				return std::make_unique<ProjectileAttackComponent>();
			}
		};
	}
}
