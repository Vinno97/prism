#pragma once
#include <stdexcept>

namespace ECS {
	namespace Components {
		struct Component {
			virtual Component* Clone() = 0;
		};
	}
}