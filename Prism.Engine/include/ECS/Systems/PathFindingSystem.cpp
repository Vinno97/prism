#include "PathFindingSystem.h"

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;

PathFindingSystem::PathFindingSystem(EntityManager & entityManager) : System(entityManager)
{
}

PathFindingSystem::~PathFindingSystem()
{
}

void PathFindingSystem::update(Context context)
{
}

System * PathFindingSystem::clone()
{
	return nullptr;
}
