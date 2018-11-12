#pragma once
#include <vector>
#include "BoundingBox.h"

namespace Physics {
	class QuadTree
	{
	public:
		/// <summary>
		/// create quadtree
		/// </summary>
		QuadTree();

		/// <summary>
		/// create quadtree
		/// </summary>
		/// <param name="width">Total width of the highest level quadtree</param>
		/// <param name="height">Total height of the highest level quadtree</param>
		/// <param name="width">The center x coördinate of the highest level quadtree</param>
		/// <param name="width">Total width of the highest level quadtree</param>
		QuadTree(float width, float heigt, float x, float y, unsigned int maxObject);

		/// <summary>
		/// Clear the contents of the quadtree
		/// </summary>
		void Clear();

		/// <summary>
		/// Split the quadtree in 4 equal quadtrees
		/// </summary>
		void Split();

		/// <summary>
		/// Insert a new boundingbox in the quadtree
		/// </summary>
		/// <param name="newBox">The boundingbox that needs to be inserted in the quadtree</param>
		void Insert(BoundingBox const &newBox);

		/// <summary>
		/// Retrieve a vector with al the boundingboxes that can collide with the given boundingbox
		/// </summary>
		///<param name="searchBox">A vector will be returned that could collide with this boundingbox</param>
		std::vector<BoundingBox const *> Retrieve(std::vector<BoundingBox const *> &vector, BoundingBox const &searchBox);

		/// <summary>
		/// Get the bounds of the quadtree;
		/// </summary>
		const BoundingBox GetBounds() const;

		///<summary>///
		/// Get max amount of object before the quadtree splits
		///</summary>///
		unsigned int GetMaxObject() const;
	private:
		unsigned int maxObjects;
		std::vector<BoundingBox const * > objects;
		Physics::BoundingBox bounds;

		//0 = North East
		//1 = South East
		//2 = South West
		//3 = North East
		QuadTree *nodes[4]{ nullptr };

		/// <summary>
		/// Get the index of the where the new boundingbox should be placed
		/// </summary>
		/// <param name="box">The boundingbox of which the index is needed</param>
		int GetIndex(BoundingBox const &box) const;
	};
}
