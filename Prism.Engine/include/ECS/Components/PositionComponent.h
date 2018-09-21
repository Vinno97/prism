#pragma once

#include "Component.h"


namespace ECS {
	namespace Components {
		struct PositionComponent : public Component {
			int x;
			int y;
		};
	}
}