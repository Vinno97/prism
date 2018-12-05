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

		/// <summary>
		/// Create boundingbox
		/// </summary>
		/// <param name="north">The distance of the northern edges to the center of the boundingbox </param>
		/// <param name="east">The distance of the eastern edges to the center of the boundingbox </param>
		/// <param name="south">The distance of the southern edges to the center of the boundingbox </param>
		/// <param name="west">The distance of the western edges to the center of the boundingbox </param>
		/// <param name="posX">The center x coördinates of the bounding box</param>
		/// <param name="posY">A boundingbox </param>
		BoundingBox(float north, float east, float south, float west, float posX, float posY);

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

		/// <summary>
		/// Set the bounds of the boundingbox
		/// </summary>
		/// <param name="north">The distance of the northern edges to the center of the boundingbox </param>
		/// <param name="east">The distance of the eastern edges to the center of the boundingbox </param>
		/// <param name="south">The distance of the southern edges to the center of the boundingbox </param>
		/// <param name="west">The distance of the western edges to the center of the boundingbox </param>
		void SetBounds(float north, float east, float south, float west);

		/// <summary>
		/// Get the x position of the boundingbox
		/// </summary>
		float GetPosX() const;

		/// <summary>
		/// Get the y position of the boundingbox
		/// </summary>
		float GetPosY() const;

		/// <summary>
		/// Get the north bound of the boundingbox
		/// </summary>
		float GetNorth() const;

		/// <summary>
		/// Get the north coördinate of the boundingbox
		/// </summary>
		float GetAbsNorth() const;

		/// <summary>
		/// Get the east bound of the boundingbox
		/// </summary>
		float GetEast() const;
		
		/// <summary>
		/// Get the east coördinate of the boundingbox
		/// </summary>
		float GetAbsEast() const;

		/// <summary>
		/// Get the south bound of the boundingbox
		/// </summary>
		float GetSouth() const;

		/// <summary>
		/// Get the south coördinate of the boundingbox
		/// </summary>
		float GetAbsSouth() const;

		/// <summary>
		/// Get the west bound of the boundingbox
		/// </summary>
		float GetWest() const;

		/// <summary>
		/// Get the west coördinate of the boundingbox
		/// </summary>
		float GetAbsWest() const;

	private:

		//Center x position of the boundingbox 
		float posX = 0;

		//Center y position of the boundingbox
		float posY = 0;

		//The distance of the northern edges to the center of the boundingbox 
		float north = 0;

		//The distance of the eastern edges to the center of the boundingbox
		float east = 0;

		//The distance of the southern edges to the center of the boundingbox
		float south = 0;

		//The distance of the western edges to the center of the boundingbox
		float west = 0;
	};
}

