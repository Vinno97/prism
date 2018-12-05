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
		/// <param name="x">The center x co�rdinates of the bounding box</param>
		/// <param name="y">A boundingbox </param>
		BoundingBox(float radius, float posX, float posY);

		/// <summary>
		/// Create boundingbox
		/// </summary>
		/// <param name="north">The distance of the northern edges to the center of the boundingbox </param>
		/// <param name="east">The distance of the eastern edges to the center of the boundingbox </param>
		/// <param name="south">The distance of the southern edges to the center of the boundingbox </param>
		/// <param name="west">The distance of the western edges to the center of the boundingbox </param>
		/// <param name="x">The center x co�rdinates of the bounding box</param>
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
		/// <param name="posX">The center x co�rdinates of the bounding box</param>
		/// <param name="posY">A boundingbox </param>
		//BoundingBox(float north, float east, float south, float west, float posX, float posY);

		/// <summary>
		/// Deconstruct boundingbox
		/// </summary>
		~BoundingBox();

		/// <summary>
		/// Set the center position of the boundingbox
		/// </summary>
		/// <param name="posX">The center x co�rdinates of the bounding box</param>
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
		/// Set the bounds of the boundingbox
		/// </summary>
		float GetPosX() const;

		/// <summary>
		/// Set the bounds of the boundingbox
		/// </summary>
		float GetPosY() const;

		float GetPosZ() const;

		/// <summary>
		/// Set the bounds of the boundingbox
		/// </summary>
		float GetNorth() const;

		/// <summary>
		/// Set the bounds of the boundingbox
		/// </summary>
		float GetEast() const;

		/// <summary>
		/// Set the bounds of the boundingbox
		/// </summary>
		float GetSouth() const;

		/// <summary>
		/// Set the bounds of the boundingbox
		/// </summary>
		float GetWest() const;

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

