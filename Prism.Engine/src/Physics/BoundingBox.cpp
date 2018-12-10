#include "Physics/BoundingBox.h"

using namespace Physics;

BoundingBox::BoundingBox()
= default;

BoundingBox::BoundingBox(float radius, float posX, float posY)
{
	SetPosXY(posX, posY);
	SetBounds(radius, radius, -1 * radius, -1 * radius);
}

BoundingBox::BoundingBox(float north, float east, float south, float west)
{
	SetPosXY(0, 0);
	SetBounds(north, east, south, west);
}

BoundingBox::BoundingBox(float north, float east, float south, float west, float posX, float posY)
{
	SetPosXY(posX, posY);
	SetBounds(north, east, south, west);
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::SetPosXY(float posX, float posY)
{
	this->posX = posX;
	this->posY = posY;
}

void BoundingBox::SetBounds(float north, float east, float south, float west)
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
