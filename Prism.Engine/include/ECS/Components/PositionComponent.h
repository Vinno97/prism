#pragma once

#include "Component.h"


namespace ECS {
	namespace Components {
		struct PositionComponent : Component {
			int x;
			int y;
		};
	}
}