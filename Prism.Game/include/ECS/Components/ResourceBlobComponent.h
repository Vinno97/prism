#pragma once

#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct ResourceBlobComponent : Component {
			Component* Clone() override {
				return new ResourceBlobComponent();
			}
		};
	}
}