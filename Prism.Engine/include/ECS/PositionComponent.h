#pragma once
#include "ECS/Component.h"

namespace ECS {
	struct PositionComponent : Component {
		int x;
		int y;
	};
}