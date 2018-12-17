#include "World/Assemblers/MineAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/MineComponent.h"

void World::Assemblers::MineAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const
{
    if (worldObject.gid == 20)
    {
        EntityFactory::getInstance().createMine(entity, entityManager);
    }
}

void World::Assemblers::MineAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const
{
    if (entityManager.hasComponent<ECS::Components::MineComponent>(entity))
    {
        worldObject.gid = 20;
    }
}
