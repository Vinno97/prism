#include "Physics/QuadTree.h"
#include <iostream>

using namespace Physics;

QuadTree::QuadTree()
= default;

QuadTree::~QuadTree() {
	Clear();
}

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

QuadTree::QuadTree(const QuadTree& other)
{
	this->maxObjects = other.maxObjects;
	this->objects = other.objects;
	this->bounds = other.bounds;
	if (other.nodes[0] != nullptr) {
		for (int i = 0; i < 4;i++) {
			nodes[i] = new QuadTree();
			*nodes[i] = *other.nodes[i];
		}
	}
}

QuadTree & QuadTree::operator=(const QuadTree& other)
{
	if (this != &other) {
		this->maxObjects = other.maxObjects;
		this->objects = other.objects;
		this->bounds = other.bounds;
		if (other.nodes[0] != nullptr) {
			for (int i = 0; i < 4;i++) {
				nodes[i] = new QuadTree();
				*nodes[i] = *other.nodes[i];
			}
		}
		return *this;
	}
}

QuadTree::QuadTree(QuadTree&& other)
{
	this->maxObjects = other.maxObjects;
	other.maxObjects = 0;
	this->objects = other.objects;
	other.objects.clear();
	this->bounds = other.bounds;
	other.bounds = BoundingBox();
	for (int i = 0; i < 4;i++) {
		nodes[i] = other.nodes[i];
		other.nodes[i] = nullptr;
	}
}

QuadTree & QuadTree::operator=(QuadTree&& other)
{
	if (this != &other) {
		this->maxObjects = other.maxObjects;
		other.maxObjects = 0;
		this->objects = other.objects;
		other.objects.clear();
		this->bounds = other.bounds;
		other.bounds = BoundingBox();
		for (int i = 0; i < 4;i++) {
			nodes[i] = other.nodes[i];
			other.nodes[i] = nullptr;
		}
	}
	return *this;
}

void QuadTree::Clear()
{
	if (nodes[0] != nullptr) {
		for (auto i = 0;i < 4; i++) {
			delete nodes[i];
			nodes[i] = nullptr;
		}
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

	nodes[0] = new QuadTree(width, height, east, north, maxObjects);
	nodes[1] = new QuadTree(width, height, east, south, maxObjects);
	nodes[2] = new QuadTree(width, height, west, south, maxObjects);
	nodes[3] = new QuadTree(width, height, west, north, maxObjects);

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
	bool fitLeft = bEast <= qX && bWest >= qWest;


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