#pragma once
#include "Component.h"
#include "Physics/BoundingBox.h"

namespace ECS {
	namespace Components {
		struct BoundingBoxComponent : Component {
			BoundingBox boundingBox = BoundingBox(0, 0, 0, 0, 0, 0);
		};
	}
}