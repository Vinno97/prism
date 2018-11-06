#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct SceneComponent: Component {
			float ambientLightStrength;
		};
	}
}