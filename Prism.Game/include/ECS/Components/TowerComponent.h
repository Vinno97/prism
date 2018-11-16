#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct TowerComponent : Component {
			Component* Clone() override {
				return new TowerComponent();
			}
		};
	}
}