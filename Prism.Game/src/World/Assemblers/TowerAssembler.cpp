#include "World/Assemblers/TowerAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/TowerComponent.h"

using namespace World;
using namespace World::Assemblers;

void TowerAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 7) {
		EntityFactory().createTower(entity, entityManager);
	}
}

void TowerAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::TowerComponent>(entity)) {
		worldObject.gid = 7;
	}
}
