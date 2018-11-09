#pragma once

namespace ECS {
	namespace Components {
		struct Component {
			Component* Clone() {
				return new Component();
			}
		};
	}
}