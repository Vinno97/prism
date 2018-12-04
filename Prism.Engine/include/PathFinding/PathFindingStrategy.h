#pragma once

#include <Math/Vector2.h>
#include <ECS/EntityManager.h>
namespace PathFinding {
	class PathFindingStrategy {
	public:
		virtual Math::Vector2d operator()(ECS::EntityManager &entityManager, Math::Vector2d subject, Math::Vector2d target) = 0;
	};
}