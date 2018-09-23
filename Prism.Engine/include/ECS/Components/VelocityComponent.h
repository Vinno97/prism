#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct VelocityComponent : Component {
			float dx = 0;
			float dy = 0;
		};
	}
}