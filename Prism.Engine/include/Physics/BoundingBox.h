#pragma once
class BoundingBox
{
public:
	/// <sumary>
	/// Create AABBCollider
	/// </sumary>
	BoundingBox();

	/// <sumary>
	/// Create AABBCollider
	/// </sumary>
	/// <param name="radius">The distance of the edges to the center of the boundingbox </param>
	/// <param name="x">The center x coördinates of the bounding box</param>
	/// <param name="y">A boundingbox </param>
	BoundingBox(float radius, float posX, float posY);
	
	/// <sumary>
	/// Create AABBCollider
	/// </sumary>
	/// <param name="north">The distance of the edges to the center of the boundingbox </param>
	/// <param name="east">The distance of the edges to the center of the boundingbox </param>
	/// <param name="south">The distance of the edges to the center of the boundingbox </param>
	/// <param name="west">The distance of the edges to the center of the boundingbox </param>
	/// <param name="x">The center x coördinates of the bounding box</param>
	/// <param name="y">A boundingbox </param>

	BoundingBox(float north, float east, float south, float west);
	
	/// <sumary>
	/// Create AABBCollider
	/// </sumary>
	/// <param name="north">The distance of the edges to the center of the boundingbox </param>
	/// <param name="east">The distance of the edges to the center of the boundingbox </param>
	/// <param name="south">The distance of the edges to the center of the boundingbox </param>
	/// <param name="west">The distance of the edges to the center of the boundingbox </param>
	/// <param name="posX">The center x coördinates of the bounding box</param>
	/// <param name="posY">A boundingbox </param>
	BoundingBox(float north, float east, float south, float west, float posX, float posY);
	
	/// <sumary>
	/// Deconstruct boundingbox
	/// </sumary>
	~BoundingBox();

	void SetPosXY(float posX, float posY);
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

