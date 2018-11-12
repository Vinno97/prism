#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct KeyboardInputComponent : Component {
			Component* Clone() override {
				return new KeyboardInputComponent();
			}
		};
	}
}