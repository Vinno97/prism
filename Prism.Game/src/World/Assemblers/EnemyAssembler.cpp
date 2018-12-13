#include "World/Assemblers/EnemyAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/EnemyComponent.h"

using namespace World;
using namespace Assemblers;

void EnemyAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const
{
	if (worldObject.gid == 5)
	{
		EntityFactory().createEnemy(entity, entityManager);
	}
}

void EnemyAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const
{
	if (entityManager.hasComponent<ECS::Components::EnemyComponent>(entity))
	{
		worldObject.gid = 5;
	}
}
