#include "Physics/BoundingBox.h"

using namespace Physics;

BoundingBox::BoundingBox()
= default;

BoundingBox::BoundingBox(const float radius, const float posX, const float posY)
{
	SetPosXY(posX, posY);
	SetBounds(radius, radius, -1 * radius, -1 * radius);
}

BoundingBox::BoundingBox(const float north, const float east, const float south, const float west)
{
	SetPosXY(0, 0);
	SetBounds(north, east, south, west);
}

BoundingBox::BoundingBox(const float north, const float east, const float south, const float west, const float posX, const float posY)
{
	SetPosXY(posX, posY);
	SetBounds(north, east, south, west);
}

void BoundingBox::SetPosXY(const float posX, const float posY)
{
	this->posX = posX;
	this->posY = posY;
}

void BoundingBox::SetBounds(const float north, const float east, const float south, const float west)
{
	this->north = north;
	this->east = east;
	this->south = south;
	this->west = west;
}

float BoundingBox::GetPosX() const
{
	return posX;
}

float BoundingBox::GetPosY() const
{
	return posY;
}

float BoundingBox::GetNorthBound() const
{
	return north;
}

float Physics::BoundingBox::GetNorthCoordinate() const
{
	return posY+north;
}

float BoundingBox::GetEastBound() const
{
	return east;
}

float Physics::BoundingBox::GetEastCoordinate() const
{
	return posX+east;
}

float BoundingBox::GetSouthBound() const
{
	return south;
}

float Physics::BoundingBox::GetSouthCoordinate() const
{
	return posY+south;
}

float BoundingBox::GetWestBound() const
{
	return west;
}

float Physics::BoundingBox::GetWestCoordinate() const
{
	return posX+west;
}
