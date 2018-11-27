#pragma once
#include "Component.h"
#include "Physics/BoundingBox.h"
#include <vector>

namespace ECS {
	namespace Components {
		struct BoundingBoxComponent : Component {

			BoundingBoxComponent(float width, float height) : boundingBox(Physics::BoundingBox(height / 2.0, width / 2.0, -1 * height / 2.0, -1 * width / 2.0)) {};

			Physics::BoundingBox boundingBox;
			bool didCollide = false;

			std::vector<Physics::BoundingBox const *> collidesWith;
			
			Component* Clone() override
			{
				auto newComponent = new BoundingBoxComponent(boundingBox.GetEast() - boundingBox.GetWest(), boundingBox.GetNorth() - boundingBox.GetSouth());
				newComponent->didCollide = this->didCollide;
				for (int i = 0;i < collidesWith.size();i++) {
					newComponent->collidesWith.push_back(collidesWith[i]);
				}
				return newComponent;
			}
		};
	}
}

