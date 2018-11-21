#include "World/Assemblers/EnemySpawnAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/EnemySpawnComponent.h"

using namespace World;
using namespace World::Assemblers;

void EnemySpawnAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 8) {
		EntityFactory().createEnemy(entity, entityManager);
	}
}

void EnemySpawnAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::EnemySpawnComponent>(entity)) {
		worldObject.gid = 8;
	}
}
