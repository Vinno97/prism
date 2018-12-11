#pragma once

#include "ECS/Components/Component.h"
#include "Math/Vector3f.h"
#include "Enums/BuildTypes.h"

namespace ECS {
	namespace Components {
		struct BuildComponent : Component {

			bool isBuilding = false;
			bool isUsingMouse = false;

			int buildingId = -1;
			Enums::BuildTypes currentBuild = Enums::BuildTypes::NONE;
			Math::Vector3f buildingColor;
			float buildingScaleX;
			float buildingScaleY;
			float buildingScaleZ;
			float posX = 0;
			float posY = 0;

			std::unique_ptr<Component> clone() override {
				BuildComponent component(*this);
				return std::make_unique<BuildComponent>(component);
			}
		};
	}
}
