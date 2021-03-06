#pragma once
#include "Physics/BoundingBox.h"
#include <vector>

namespace Physics {
	class AABBCollider
	{
	public:
		/// <summary>
		/// create AABBCollider
		/// </summary>
		AABBCollider();

		/// <summary>
		/// Check whether or not two boundingboxes are colliding
		/// </summary>
		/// <param name="box1">A boundingbox </param>
		/// <param name="box2">A boundingbox </param>
		bool CheckCollision(BoundingBox const &box1, BoundingBox const &box2) const;
	};
}

