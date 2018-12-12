#include "Physics/AABBCollider.h"

using namespace Physics;

AABBCollider::AABBCollider()
= default;

bool AABBCollider::CheckCollision(BoundingBox const &box1, BoundingBox const &box2) const
{
	//check for collision on vertical axis
	float vert1 = (box1.GetNorthCoordinate()) - (box2.GetSouthCoordinate());
	float vert2 = (box1.GetSouthCoordinate()) - (box2.GetNorthCoordinate());
	float vert = vert1 * vert2;

	//check for collision on horizontal axis
	float horz1 = (box1.GetEastCoordinate()) - (box2.GetWestCoordinate());
	float horz2 = (box1.GetWestCoordinate()) - (box2.GetEastCoordinate());
	float horz = horz1 * horz2;

	return vert < 0 && horz < 0;
}