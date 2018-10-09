#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct PositionComponent : Component {

			/// <summary>
			///	The position in units
			/// </summary>
			double x = 0;

			/// <summary>
			///	The position in units
			/// </summary>
			double y = 0;
		};
	}
}