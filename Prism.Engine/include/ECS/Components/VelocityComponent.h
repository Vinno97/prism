#pragma once

#include "Component.h"

namespace ECS {
	namespace Components {
		struct VelocityComponent : Component {

			/// <summary>
			///	The amount of delta X in units/second
			/// </summary>
			double dx = 0;

			/// <summary>
			///	The amount of delta Y in units/second
			/// </summary>
			double dy = 0;
		};
	}
}