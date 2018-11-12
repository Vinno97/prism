#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct EnemyComponent : Component {
			Component* Clone() override {
				return new EnemyComponent();
			}
		};
	}
}