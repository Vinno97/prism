#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct PositionComponent : Component {
			PositionComponent() = default;
			PositionComponent(double x_, double y_) : x(x_), y(y_) { };

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