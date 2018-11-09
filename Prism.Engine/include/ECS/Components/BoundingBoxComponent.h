#pragma once
#include "Component.h"
#include "Physics/BoundingBox.h"

struct BoundingBoxComponent : ECS::Components::Component {
	BoundingBoxComponent() = default;
	BoundingBoxComponent(BoundingBox boundingBox_) : boundingBox(boundingBox_) {};

	/// <summary>
	///	The boundingbox
	/// </summary>
	BoundingBox boundingBox;
};
