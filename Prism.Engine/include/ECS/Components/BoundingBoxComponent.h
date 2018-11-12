#pragma once
#include "ECS/Components/Component.h"
#include "Physics/BoundingBox.h"

struct BoundingBoxComponent : ECS::Component{
	BoundingBoxComponent() = default;
	BoundingBoxComponent(float width, float height) : boundingBox(height / 2.0, width / 2.0, -1 * height / 2.0, -1 * width / 2.0) {};

	/// <summary>
	///	The boundingbox
	/// </summary>
	BoundingBox boundingBox;
	Component* Clone() override
	{
		auto b = new BoundingBoxComponent(boundingBox.GetEast() - boundingBox.GetWest(), boundingBox.GetNorth() - boundingBox.GetSouth());
		return b;
	}
};
