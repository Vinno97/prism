#include "Physics/AABBCollider.h"



AABBCollider::AABBCollider()
{
}


AABBCollider::~AABBCollider()
{
}

bool CheckCollision(BoundingBox box1, BoundingBox box2) 
{
	int vert1 = (box1.North + box1.posY) - (box2.South + box2.posY);
	int vert2 = (box1.South + box1.posY) - (box2.North + box2.posY);
	int vert = vert1 * vert2;

	int horz1 = (box1.East + box1.posX) - (box2.West + box2.posX);
	int horz2 = (box1.West + box1.posX) - (box2.East + box2.posX);
	int horz = vert1 * vert2;

	return vert < 0 && horz < 0;
}
