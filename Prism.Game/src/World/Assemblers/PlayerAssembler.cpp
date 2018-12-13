#include "World/Assemblers/PlayerAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/PlayerComponent.h"

using namespace World;
using namespace Assemblers;

void PlayerAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const
{
	if (worldObject.gid == 4)
	{
		EntityFactory().createPlayer(entity, entityManager);
	}
}

void PlayerAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const
{
	if (entityManager.hasComponent<ECS::Components::PlayerComponent>(entity))
	{
		worldObject.gid = 4;
	}
}
