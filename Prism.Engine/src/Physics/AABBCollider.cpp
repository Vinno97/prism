#include "Physics/AABBCollider.h"

using namespace Physics;

AABBCollider::AABBCollider()
= default;

bool AABBCollider::CheckCollision(BoundingBox const &box1, BoundingBox const &box2)
{
	float vert1 = (box1.GetNorth() + box1.GetPosY()) - (box2.GetSouth() + box2.GetPosY());
	float vert2 = (box1.GetSouth() + box1.GetPosY()) - (box2.GetNorth() + box2.GetPosY());
	float vert = vert1 * vert2;

	float horz1 = (box1.GetEast() + box1.GetPosX()) - (box2.GetWest() + box2.GetPosX());
	float horz2 = (box1.GetWest() + box1.GetPosX()) - (box2.GetEast() + box2.GetPosX());
	float horz = horz1 * horz2;

	float z1 = (box1.GetUp() + box1.GetPosZ()) - (box2.GetDown() + box2.GetPosZ());
	float z2 = (box1.GetDown() + box1.GetPosZ()) - (box2.GetUp() + box2.GetPosZ());
	float depth = z1 * z2;

	return vert < 0 && horz < 0 && depth < 0;
}