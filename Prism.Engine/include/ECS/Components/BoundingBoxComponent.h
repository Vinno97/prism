#pragma once
#include "Component.h"
#include "Physics/BoundingBox.h"
#include <vector>

namespace ECS {
	namespace Components {
		struct BoundingBoxComponent : public Component {

			BoundingBoxComponent(float width, float height) : boundingBox(Physics::BoundingBox(height / 2.0, width / 2.0, -1 * height / 2.0, -1 * width / 2.0)) {};
			BoundingBoxComponent(float width, float height, float depth) : boundingBox(Physics::BoundingBox(height / 2.0, width / 2.0, -1 * height / 2.0, -1 * width / 2.0, depth/ 2.0, -1* depth/2.0)) {};
			BoundingBoxComponent(float north, float east, float south, float west, float up, float down) : boundingBox(Physics::BoundingBox(north,east,south,west,up,down)) {};

			Physics::BoundingBox boundingBox;
			bool didCollide = false;

			std::vector<unsigned int> collidesWith;
			
			std::unique_ptr<Component> clone() override
			{
				auto newComponent = std::make_unique <BoundingBoxComponent>(boundingBox.GetNorthBound(),boundingBox.GetEastBound(), boundingBox.GetSouthBound(),boundingBox.GetWestBound(),boundingBox.GetUp(),boundingBox.GetDown());
				newComponent->didCollide = this->didCollide;
				newComponent->boundingBox.SetPosXYZ(this->boundingBox.GetPosX(), this->boundingBox.GetPosY(), this->boundingBox.GetPosZ());
				for (int i = 0;i < collidesWith.size();i++) {
					newComponent->collidesWith.push_back(collidesWith[i]);
				}
				return newComponent;
			}
		};
	}
}