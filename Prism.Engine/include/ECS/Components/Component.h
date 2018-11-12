#pragma once
#include <stdexcept>

namespace ECS {
	namespace Components {
		struct Component {
			virtual Component* Clone() = 0;
			//	throw new std::exception("This method should never be called!");
			//}
		};
	}
}