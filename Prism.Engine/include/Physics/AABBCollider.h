#pragma once
#include "Physics/BoundingBox.h"

class AABBCollider
{
public:
	AABBCollider();
	~AABBCollider();
	bool CheckCollision(BoundingBox box1, BoundingBox box2);
};

