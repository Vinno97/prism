#pragma once
#include <vector>
#include "BoundingBox.h"
class QuadTree
{
public:
	QuadTree();
	QuadTree(float width, float Heigt, float x, float y);
	~QuadTree();
	void Clear();
	void Split();
	int GetIndex(BoundingBox const &box) const;
	void Insert(BoundingBox const &newBox);
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

	
};

