#pragma once
#pragma once

#include "Component.h"


namespace ECS {
	namespace Components {
		struct VelocityComponent : public Component {
			float dx;
			float dy;
		};
	}
}