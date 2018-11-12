#include "Physics/BoundingBox.h"


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

float BoundingBox::GetNorth() const
{
	return north;
}

float BoundingBox::GetEast() const
{
	return east;
}

float BoundingBox::GetSouth() const
{
	return south;
}

float BoundingBox::GetWest() const
{
	return west;
}
