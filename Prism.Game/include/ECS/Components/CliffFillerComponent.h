#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct CliffFillerComponent : Component {
			Component* Clone() override {
				return new CliffFillerComponent();
			}
		};
	}
}