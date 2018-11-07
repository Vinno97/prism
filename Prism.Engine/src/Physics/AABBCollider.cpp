#include "Physics/AABBCollider.h"


AABBCollider::AABBCollider()
{
}


AABBCollider::~AABBCollider()
{
}


bool AABBCollider::CheckCollision(BoundingBox box1, BoundingBox box2)
{
	float vert1 = (box1.GetNorth() + box1.GetPosY()) - (box2.GetSouth() + box2.GetPosY());
	float vert2 = (box1.GetSouth() + box1.GetPosY()) - (box2.GetNorth() + box2.GetPosY());
	float vert = vert1 * vert2;

	float horz1 = (box1.GetEast() + box1.GetPosX()) - (box2.GetWest() + box2.GetPosX());
	float horz2 = (box1.GetWest() + box1.GetPosX()) - (box2.GetEast() + box2.GetPosX());
	float horz = horz1 * horz2;

	return vert < 0 && horz < 0;
}