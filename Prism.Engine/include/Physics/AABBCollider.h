#pragma once
#include "Physics/BoundingBox.h"

namespace Physics {
	class AABBCollider
	{
	public:
		/// <summary>
		/// create AABBCollider
		/// </summary>
		AABBCollider();

		/// <summary>
		/// Deconstruct AABBCollider
		/// </summary>
		~AABBCollider();

		/// <summary>
		/// Check whethor or not two boundingboxes are colliding
		/// </summary>
		/// <param name="box1">A boundingbox </param>
		/// <param name="box2">A boundingbox </param>
		bool CheckCollision(BoundingBox const &box1, BoundingBox const &box2);
		int GetCollideSide(BoundingBox const &box1, BoundingBox const &box2);
	};
}

