#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct VelocityComponent : Component {
			float dx;
			float dy;
		};
	}
}