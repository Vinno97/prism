#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct TreeComponent : Component {
			Component* Clone() override {
				return new TreeComponent();
			}
		};
	}
}