#include "Physics/QuadTree.h"
#include <iostream>

using namespace Physics;

QuadTree::QuadTree(float width, float heigt, float x, float y, unsigned int maxObjects)
{
	float halfwidth = width / 2.0;
	float halfHeigth = heigt / 2.0;
	this->bounds = BoundingBox(halfHeigth, halfwidth, -1 * halfHeigth, -1 * halfwidth, x, y);
	this->maxObjects = maxObjects;
}

void QuadTree::Clear()
{
	objects.clear();
}

void QuadTree::Split()
{
	float width = bounds.GetEastBound();
	float height = bounds.GetNorthBound();
	float halfwidth = width / 2.0;
	float halfHeight = height / 2.0;
	float east = halfwidth + bounds.GetPosX();
	float west = (-1 * halfHeight) + bounds.GetPosX();
	float north = halfHeight + bounds.GetPosY();
	float south = (-1 * halfHeight) + bounds.GetPosY();

	nodes[0] = std::make_unique<QuadTree>(width, height, east, north, maxObjects);
	nodes[1] = std::make_unique<QuadTree>(width, height, east, south, maxObjects);
	nodes[2] = std::make_unique<QuadTree>(width, height, west, south, maxObjects);
	nodes[3] = std::make_unique<QuadTree>(width, height, west, north, maxObjects);

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
	float qNorth = std::abs(bounds.GetNorthCoordinate());
	float qEast = std::abs(bounds.GetEastCoordinate());
	float qSouth = std::abs(bounds.GetSouthCoordinate());
	float qWest = std::abs(bounds.GetWestCoordinate());

	float bX = box.GetPosX();
	float bY = box.GetPosY();
	float bNorth = std::abs(box.GetNorthCoordinate());
	float bEast = std::abs(box.GetEastCoordinate());
	float bSouth = std::abs(box.GetSouthCoordinate());
	float bWest = std::abs(box.GetWestCoordinate());


	bool fitTop = qNorth - bNorth >= 0 && bSouth - qY >= 0;
	bool fitRight = qEast - bEast >= 0 && bWest - qX >= 0;

	bool fitBottom = qY - bNorth >= 0  && bSouth - qSouth >= 0;
	bool fitLeft = qX - bEast >= 0 && bWest - qWest >= 0;

	if (fitTop) {
		if (fitRight) {
			index = 0;
		}
		else if (fitLeft) {
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

void QuadTree::RetrieveAll(std::list<BoundingBox const *> &boundingBoxes, BoundingBox const &searchBox)
{
	int index = GetIndex(searchBox);
	if (index != -1 && nodes[0] != nullptr) {
		nodes[index]->RetrieveAll(boundingBoxes, searchBox);
	}
	else if (nodes[0] != nullptr) {
		nodes[0]->RetrieveAll(boundingBoxes, searchBox);
		nodes[1]->RetrieveAll(boundingBoxes, searchBox);
		nodes[2]->RetrieveAll(boundingBoxes, searchBox);
		nodes[3]->RetrieveAll(boundingBoxes, searchBox);
	}
	std::copy(objects.begin(), objects.end(), std::back_inserter(boundingBoxes));
}

const BoundingBox QuadTree::GetBounds() const
{
	return bounds;
}

unsigned int QuadTree::GetMaxObject() const
{
	return maxObjects;
}