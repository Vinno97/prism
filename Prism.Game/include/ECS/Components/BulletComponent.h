#pragma once

#include "ECS/Components/Component.h"

namespace ECS {
	namespace Components {
		struct BulletComponent : Component {
			float lifeTime;

			Component* Clone() override {
				return new BulletComponent();
			}
		};
	}
}