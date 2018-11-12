#include "Physics/QuadTree.h"

using namespace Physics;

QuadTree::QuadTree()
= default;

QuadTree::QuadTree(float width, float heigt, float x, float y, unsigned int maxObjects)
{
	float halfwidth = width / 2.0;
	float halfHeigth = heigt / 2.0;
	this->bounds = BoundingBox(halfHeigth, halfwidth, -1 * halfHeigth, -1 * halfwidth, x, y);
	nodes[0] = nullptr;
	nodes[1] = nullptr;
	nodes[2] = nullptr;
	nodes[3] = nullptr;
	this->maxObjects = maxObjects;
}

void QuadTree::Clear()
{
	for (auto i = 0;i < 4; i++) {
		objects.clear();
		nodes[i] = nullptr;
	}
	objects.clear();
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

	nodes[0] = &QuadTree(width, height, east, north, maxObjects);
	nodes[1] = &QuadTree(width, height, east, south, maxObjects);
	nodes[2] = &QuadTree(width, height, west, south, maxObjects);
	nodes[3] = &QuadTree(width, height, west, north, maxObjects);
	
	for (auto it = objects.begin(); it != objects.end();) {
		int index = GetIndex(*(*it));
		if (index != -1) {
			nodes[index]->Insert(*(*it));
			it = objects.erase(it);
		}
		else {
			it++;
		}
	}
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

	objects.push_back(&newBox);

	if (objects.size() > maxObjects) {
		if (nodes[0] == nullptr) {
			Split();
			
		}
	}
}

std::vector<BoundingBox const *> QuadTree::Retrieve(std::vector<BoundingBox const *> &vector,BoundingBox const &searchBox)
{
	int index = GetIndex(searchBox);
	if (index != -1 && nodes[0] != nullptr) {
		nodes[index]->Retrieve(vector,searchBox);
	}
	vector.insert(vector.end(),objects.begin(), objects.end());
	return vector;
}

const BoundingBox QuadTree::GetBounds() const
{
	return bounds;
}

unsigned int QuadTree::GetMaxObject() const
{
	return maxObjects;
}
