#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct DragComponent : Component {
			/// <summary>
			///	The amount of drag in units/second^2
			/// </summary>
			double force = 0;
		};
	}
}