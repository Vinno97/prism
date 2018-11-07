#pragma once
class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(float radius, float x, float y);
	BoundingBox(float north, float east, float south, float west);
	BoundingBox(float north, float east, float south, float west, float posX, float posY);
	~BoundingBox();
	void SetPosXY(float x, float y);
	void SetBounds(float north, float east, float south, float west);
	float GetPosX() const;
	float GetPosY() const;
	float GetNorth() const;
	float GetEast() const;
	float GetSouth() const;
	float GetWest() const;
private:
	float posX;
	float posY;
	float north;
	float east;
	float south;
	float west;
};

