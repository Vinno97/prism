#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct PlacableComponent : Component {
			float lifeTime;

			Component* Clone() override {
				return new PlacableComponent();
			}
		};
	}
}