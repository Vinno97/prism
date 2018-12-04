#pragma once

#include "ECS/Components/Component.h"
#include "PathFinding/Strategies.h"

namespace ECS {
	namespace Components {
		struct TargetComponent : Component {

			unsigned target;
			PathFinding::Strategies::PathFindingStrategy strategy{PathFinding::Strategies::LINEAR};

			std::unique_ptr<Component> clone() override {
				return std::make_unique<TargetComponent>();
			}
		};
	}
}
