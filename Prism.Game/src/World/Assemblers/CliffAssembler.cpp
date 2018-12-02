#include "World/Assemblers/CliffAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffComponent.h"

using namespace World;
using namespace World::Assemblers;

void CliffAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 5) {
		EntityFactory().createCliff(entity, entityManager, 180);
	}	else if (worldObject.gid == 6) {
		EntityFactory().createCliff(entity, entityManager, 90);
	}	else if (worldObject.gid == 8) {
		EntityFactory().createCliff(entity, entityManager, 0);
	}	else if (worldObject.gid == 7) {
		EntityFactory().createCliff(entity, entityManager, 270);
	}
}

void CliffAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::CliffComponent>(entity)) {
		worldObject.gid = 5;
		worldObject.gid = 6;
		worldObject.gid = 7;
		worldObject.gid = 8;
	}
}