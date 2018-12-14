#include "World/Assemblers/CliffCornerAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffCornerComponent.h"

using namespace World;
using namespace World::Assemblers;

void CliffCornerAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 13) {
		EntityFactory().createCliffCorner(entity, entityManager, 0);
	}
	else if (worldObject.gid == 14) {
		EntityFactory().createCliffCorner(entity, entityManager, 270);
	}
	else if (worldObject.gid == 15) {
		EntityFactory().createCliffCorner(entity, entityManager, 180);
	}
	else if (worldObject.gid == 16) {
		EntityFactory().createCliffCorner(entity, entityManager, 90);
	}
}

void CliffCornerAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::CliffCornerComponent>(entity)) {
		worldObject.gid = 13;
		worldObject.gid = 14;
		worldObject.gid = 15;
		worldObject.gid = 16;
	}
}