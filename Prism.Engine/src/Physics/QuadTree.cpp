#include "Physics/QuadTree.h"



QuadTree::QuadTree()
= default;

QuadTree::QuadTree(float width, float heigt, float x, float y)
{
	float halfwidth = width / 2.0;
	float halfHeigth = heigt / 2.0;
	this->bounds = BoundingBox(halfHeigth, halfwidth, -1 * halfHeigth, -1 * halfwidth, x, y);
	nodes[0] = nullptr;
	nodes[1] = nullptr;
	nodes[2] = nullptr;
	nodes[3] = nullptr;
}


QuadTree::~QuadTree()
{
	Clear();
}

void QuadTree::Clear()
{
	for (QuadTree *node : nodes) {
		if (node != nullptr) {
			delete node;
		}
	}
}

void QuadTree::Split()
{
	float width = bounds.GetEast();
	float height = bounds.GetNorth();
	float halfwidth = width / 2.0;
	float halfHeight = height / 2.0;
	float east = halfwidth + bounds.GetPosX();
	float west = (-1 * halfHeight) + bounds.GetPosX();
	float north = halfHeight + bounds.GetPosY();
	float south = (-1 * halfHeight) + bounds.GetPosY();

	nodes[0] = new QuadTree(width, height, east, north);
	nodes[1] = new QuadTree(width, height, east, south);
	nodes[2] = new QuadTree(width, height, west, south);
	nodes[3] = new QuadTree(width, height, west, north);
}

int QuadTree::GetIndex(BoundingBox const &box) const
{
	int index = -1;
	
	float qX = bounds.GetPosX();
	float qY = bounds.GetPosY();
	float qNorth = bounds.GetNorth() + qY;
	float qEast = bounds.GetEast() + qX;
	float qSouth = bounds.GetSouth() + qY;
	float qWest = bounds.GetWest() + qX;

	float bX = box.GetPosX();
	float bY = box.GetPosY();
	float bNorth = box.GetNorth() + bY;
	float bEast = box.GetEast() + bX;
	float bSouth = box.GetSouth() + bY;
	float bWest = box.GetWest() + bX;


	bool fitTop = bNorth <= qNorth && bSouth >= qY;
	bool fitRight = bEast <= qEast && bWest >= qX;

	bool fitBottom = bNorth <= qY && bSouth >= qSouth;
	bool fitLeft =  bEast <= qX && bWest >= qWest;
	

	if (fitTop) {
		if (fitRight) {
			index = 0;
		}
		else if(fitLeft){
			index = 3;
		}
	}
	else if (fitBottom) {
		if (fitRight) {
			index = 1;
		}
		else if (fitLeft) {
			index = 2;
		}
	}

	return index;
}

void QuadTree::Insert(BoundingBox const &newBox)
{
	if (nodes[0] != nullptr) {
		int index = GetIndex(newBox);

		if (index != -1) {
			nodes[index]->Insert(newBox);

			return;
		}
	}

	objects.push_back(newBox);

	if (objects.size() > maxObjects) {
		if (nodes[0] == nullptr) {
			Split();

			//TODO: put in split functies
			for (auto it = objects.begin(); it != objects.end();) {
				int index = GetIndex(*it);
				if (index != -1) {
					nodes[index]->Insert(*it);
					it = objects.erase(it);
				}
				else {
					it++;
				}

			}
		}
	}
}

std::vector<BoundingBox> QuadTree::Retrieve(BoundingBox const &searchBox)
{
	int index = GetIndex(searchBox);
	if (index != -1 && nodes[0] != nullptr) {
		return nodes[index]->Retrieve(searchBox);
	}
	return objects;
}
