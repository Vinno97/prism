#pragma once
#include "Physics/BoundingBox.h"

class AABBCollider
{
public:
	/// <sumary>
	/// create AABBCollider
	/// </sumary>
	AABBCollider();

	/// <sumary>
	/// Deconstruct AABBCollider
	/// </sumary>
	~AABBCollider();

	/// <sumary>
	/// Check whethor or not two boundingboxes are colliding
	/// </sumary>
	/// <param name="box1">A boundingbox </param>
	/// <param name="box2">A boundingbox </param>
	bool CheckCollision(BoundingBox const &box1, BoundingBox const &box2);
};

