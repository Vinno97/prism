#pragma once

namespace Physics {
	class BoundingBox
	{
	public:
		/// <summary>
		/// Create boundingbox
		/// </summary>
		BoundingBox();

		/// <summary>
		/// Create boundingbox
		/// </summary>
		/// <param name="radius">The distance of the edges to the center of the boundingbox </param>
		/// <param name="x">The center x coördinates of the bounding box</param>
		/// <param name="y">A boundingbox </param>
		BoundingBox(float radius, float posX, float posY);

		/// <summary>
		/// Create boundingbox
		/// </summary>
		/// <param name="north">The distance of the northern edges to the center of the boundingbox </param>
		/// <param name="east">The distance of the eastern edges to the center of the boundingbox </param>
		/// <param name="south">The distance of the southern edges to the center of the boundingbox </param>
		/// <param name="west">The distance of the western edges to the center of the boundingbox </param>
		/// <param name="x">The center x coördinates of the bounding box</param>
		/// <param name="y">A boundingbox </param>

		BoundingBox(float north, float east, float south, float west);
		BoundingBox(float north, float east, float south, float west, float up, float down);

		/// <summary>
		/// Create boundingbox
		/// </summary>
		/// <param name="north">The distance of the northern edges to the center of the boundingbox </param>
		/// <param name="east">The distance of the eastern edges to the center of the boundingbox </param>
		/// <param name="south">The distance of the southern edges to the center of the boundingbox </param>
		/// <param name="west">The distance of the western edges to the center of the boundingbox </param>
		/// <param name="posX">The center x coördinates of the bounding box</param>
		/// <param name="posY">A boundingbox </param>
		//BoundingBox(float north, float east, float south, float west, float posX, float posY);

		/// <summary>
		/// Deconstruct boundingbox
		/// </summary>
		~BoundingBox();

		/// <summary>
		/// Set the center position of the boundingbox
		/// </summary>
		/// <param name="posX">The center x coördinates of the bounding box</param>
		/// <param name="posY">A boundingbox </param>
		void SetPosXY(float posX, float posY);
		void SetPosXYZ(float posX, float posY, float posZ);

		/// <summary>
		/// Set the bounds of the boundingbox
		/// </summary>
		/// <param name="north">The distance of the northern edges to the center of the boundingbox </param>
		/// <param name="east">The distance of the eastern edges to the center of the boundingbox </param>
		/// <param name="south">The distance of the southern edges to the center of the boundingbox </param>
		/// <param name="west">The distance of the western edges to the center of the boundingbox </param>
		void SetBounds(float north, float east, float south, float west);
		void SetBounds(float north, float east, float south, float west, float up, float down);
		/// <summary>
		/// Get the x position of the boundingbox
		/// </summary>
		float GetPosX() const;

		/// <summary>
		/// Get the y position of the boundingbox
		/// </summary>
		float GetPosY() const;

		float GetPosZ() const;

		/// <summary>
		/// Get the north bound of the boundingbox
		/// </summary>
		float GetNorthBound() const;

		float GetNorth() const;

		/// <summary>
		/// Get the north coordinate of the boundingbox
		/// </summary>
		float GetNorthCoordinate() const;

		/// <summary>
		/// Get the east bound of the boundingbox
		/// </summary>
		float GetEastBound() const;
		
		/// <summary>
		/// Get the east coordinate of the boundingbox
		/// </summary>
		float GetEastCoordinate() const;

		/// <summary>
		/// Get the south bound of the boundingbox
		/// </summary>
		float GetSouthBound() const;

		/// <summary>
		/// Get the south coordinate of the boundingbox
		/// </summary>
		float GetSouthCoordinate() const;

		/// <summary>
		/// Get the west bound of the boundingbox
		/// </summary>
		float GetWestBound() const;

		/// <summary>
		/// Get the west coordinate of the boundingbox
		/// </summary>
		float GetWestCoordinate() const;

		float GetUp() const;

		float GetDown() const;

	private:

		//Center x position of the boundingbox 
		float posX = 0;

		//Center y position of the boundingbox
		float posY = 0;

		float posZ = 0;

		//The distance of the northern edges to the center of the boundingbox 
		float north = 0;

		//The distance of the eastern edges to the center of the boundingbox
		float east = 0;

		//The distance of the southern edges to the center of the boundingbox
		float south = 0;

		//The distance of the western edges to the center of the boundingbox
		float west = 0;

		float up = 0;

		float down = 0;
	};
}

