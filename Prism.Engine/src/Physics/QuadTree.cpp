#include "Physics/QuadTree.h"
#include <iostream>

using namespace Physics;


QuadTree::~QuadTree()
{
	Clear();
}

QuadTree::QuadTree(const float width, const float height, float x, float y, unsigned int maxObjects)
{
	const float halfwidth = width / 2.0;
	const float halfHeigth = height / 2.0;
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
	if (other.nodes[0] != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			nodes[i] = new QuadTree();
			*nodes[i] = *other.nodes[i];
		}
	}
}

QuadTree& QuadTree::operator=(const QuadTree& other)
{
	if (this != &other)
	{
		this->maxObjects = other.maxObjects;
		this->objects = other.objects;
		this->bounds = other.bounds;
		if (other.nodes[0] != nullptr)
		{
			for (int i = 0; i < 4; i++)
			{
				nodes[i] = new QuadTree();
				*nodes[i] = *other.nodes[i];
			}
		}
	}
	return *this;
}

QuadTree::QuadTree(QuadTree&& other) noexcept
{
	this->maxObjects = other.maxObjects;
	other.maxObjects = 0;
	this->objects = other.objects;
	other.objects.clear();
	this->bounds = other.bounds;
	other.bounds = BoundingBox();
	for (int i = 0; i < 4; i++)
	{
		nodes[i] = other.nodes[i];
		other.nodes[i] = nullptr;
	}
}

QuadTree& QuadTree::operator=(QuadTree&& other) noexcept
{
	if (this != &other)
	{
		this->maxObjects = other.maxObjects;
		other.maxObjects = 0;
		this->objects = other.objects;
		other.objects.clear();
		this->bounds = other.bounds;
		other.bounds = BoundingBox();
		for (int i = 0; i < 4; i++)
		{
			nodes[i] = other.nodes[i];
			other.nodes[i] = nullptr;
		}
	}
	return *this;
}

void QuadTree::Clear()
{
	if (nodes[0] != nullptr)
	{
		for (auto i = 0; i < 4; i++)
		{
			delete nodes[i];
			nodes[i] = nullptr;
		}
	}
	objects.clear();
}

void QuadTree::Split()
{
	const float width = bounds.GetEastBound();
	const float height = bounds.GetNorthBound();
	const float halfwidth = width / 2.0;
	const float halfHeight = height / 2.0;
	const float east = halfwidth + bounds.GetPosX();
	const float west = (-1 * halfHeight) + bounds.GetPosX();
	const float north = halfHeight + bounds.GetPosY();
	const float south = (-1 * halfHeight) + bounds.GetPosY();

	nodes[0] = new QuadTree(width, height, east, north, maxObjects);
	nodes[1] = new QuadTree(width, height, east, south, maxObjects);
	nodes[2] = new QuadTree(width, height, west, south, maxObjects);
	nodes[3] = new QuadTree(width, height, west, north, maxObjects);

	for (auto it = objects.begin(); it != objects.end();)
	{
		const int index = GetIndex(*(*it));
		if (index != -1)
		{
			nodes[index]->Insert(*(*it));
			it = objects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

int QuadTree::GetIndex(BoundingBox const& box) const
{
	int index = -1;
	const float qX = bounds.GetPosX();
	const float qY = bounds.GetPosY();
	const float qNorth = std::abs(bounds.GetNorthCoordinate());
	const float qEast = std::abs(bounds.GetEastCoordinate());
	const float qSouth = std::abs(bounds.GetSouthCoordinate());
	const float qWest = std::abs(bounds.GetWestCoordinate());
	const float bX = box.GetPosX();
	const float bY = box.GetPosY();
	const float bNorth = std::abs(box.GetNorthCoordinate());
	const float bEast = std::abs(box.GetEastCoordinate());
	const float bSouth = std::abs(box.GetSouthCoordinate());
	const float bWest = std::abs(box.GetWestCoordinate());


	const bool fitTop = qNorth - bNorth >= 0 && bSouth - qY >= 0;
	const bool fitRight = qEast - bEast >= 0 && bWest - qX >= 0;

	const bool fitBottom = qY - bNorth >= 0 && bSouth - qSouth >= 0;
	const bool fitLeft = qX - bEast >= 0 && bWest - qWest >= 0;

	if (fitTop)
	{
		if (fitRight)
		{
			index = 0;
		}
		else if (fitLeft)
		{
			index = 3;
		}
	}
	else if (fitBottom)
	{
		if (fitRight)
		{
			index = 1;
		}
		else if (fitLeft)
		{
			index = 2;
		}
	}
	return index;
}

void QuadTree::Insert(BoundingBox const& newBox)
{
	if (nodes[0] != nullptr)
	{
		const int index = GetIndex(newBox);

		if (index != -1)
		{
			nodes[index]->Insert(newBox);

			return;
		}
	}

	objects.push_back(&newBox);

	if (objects.size() > maxObjects)
	{
		if (nodes[0] == nullptr)
		{
			Split();
		}
	}
}

void QuadTree::RetrieveAll(std::list<BoundingBox const *>& boundingBoxes, BoundingBox const& searchBox)
{
	const int index = GetIndex(searchBox);
	if (index != -1 && nodes[0] != nullptr)
	{
		nodes[index]->RetrieveAll(boundingBoxes, searchBox);
	}
	else if (nodes[0] != nullptr)
	{
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
