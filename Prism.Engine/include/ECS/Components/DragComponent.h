#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct DragComponent : Component {
			float force = 0;
		};
	}
}