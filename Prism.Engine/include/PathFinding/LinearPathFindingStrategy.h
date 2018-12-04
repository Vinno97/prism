#pragma once

//#include "PathFinding/PathFindingStrategy.h"
#include "PathFinding/PathFindingStrategy.h"
#include <Math/Vector2.h>
#include <ECS/EntityManager.h>

namespace PathFinding {
	class LinearPathFinding : public PathFinding::PathFindingStrategy {
	public:
		LinearPathFinding() = default;

		Math::Vector2d operator()(ECS::EntityManager &entityManager, Math::Vector2d subject, Math::Vector2d target);
	};
}