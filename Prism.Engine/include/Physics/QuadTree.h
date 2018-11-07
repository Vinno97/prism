#pragma once
#include <vector>
#include "BoundingBox.h"
class QuadTree
{
public:
	/// <sumary>
	/// create quadtree
	/// </sumary>
	QuadTree();

	/// <sumary>
	/// create quadtree
	/// </sumary>
	/// <param name="width">Total width of the highest level quadtree</param>
	/// <param name="height">Total height of the highest level quadtree</param>
	/// <param name="width">The center x coördinate of the highest level quadtree</param>
	/// <param name="width">Total width of the highest level quadtree</param>
	QuadTree(float width, float heigt, float x, float y);
	
	/// <sumary>
	/// Destructor of quadtree
	/// </sumary>
	~QuadTree();

	/// <sumary>
	/// Clear the contents of the quadtree
	/// </sumary>
	void Clear();
	
	/// <sumary>
	/// Split the quadtree in 4 equal quadtrees
	/// </sumary>
	void Split();
	
	/// <sumary>
	/// Insert a new boundingbox in the quadtree
	/// </sumary>
	/// <param name="newBox">The boundingbox that needs to be inserted in the quadtree</param>
	void Insert(BoundingBox const &newBox);

	/// <sumary>
	/// retrieve a vector with al the boundingboxes that can collide with the given boundingbox
	/// </sumary>
	///<param name="searchBox">A vector will be returned that could collide with this boundingbox</param>
	std::vector<BoundingBox> Retrieve(BoundingBox const &searchBox);
private:
	int maxObjects = 2;
	std::vector<BoundingBox> objects;
	BoundingBox bounds;
	
	//0 = North East
	//1 = South East
	//2 = South West
	//3 = North East
	QuadTree *nodes[4]{ nullptr };

	/// <sumary>
	/// Get the index of the where the new boundingbox should be placed
	/// </sumary>
	/// <param name="box">The boundingbox of which the index is needed</param>
	int GetIndex(BoundingBox const &box) const;
};

