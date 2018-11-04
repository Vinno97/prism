#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct HealthComponent : Component {
			int health;
		};
	}
}