#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct PositionComponent : Component {
			float x = 0;
			float y = 0;
		};
	}
}