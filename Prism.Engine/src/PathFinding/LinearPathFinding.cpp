#include "PathFinding/LinearPathFindingStrategy.h"

Math::Vector2d PathFinding::LinearPathFinding::operator()(ECS::EntityManager &entityManager, Math::Vector2d source,
                                                          Math::Vector2d target) {
	return (target - source).normalize();
}