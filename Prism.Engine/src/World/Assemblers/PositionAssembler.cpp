#include "World/Assemblers/PositionAssembler.h"
#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace World;
using namespace Components;
using namespace Assemblers;

void PositionAssembler::assemble(int entity, const WorldObject& worldObject, EntityManager& entityManager) const
{
	if (entityManager.hasComponent<PositionComponent>(entity))
	{
		const auto position = entityManager.getComponent<PositionComponent>(entity);
		position->x = worldObject.x;
		position->y = worldObject.y;
	}
}

void PositionAssembler::disassemble(int entity, WorldObject& worldObject, const EntityManager& entityManager) const
{
	if (entityManager.hasComponent<PositionComponent>(entity))
	{
		const auto position = entityManager.getComponent<PositionComponent>(entity);
		worldObject.x = position->x;
		worldObject.y = position->y;
	}
}
