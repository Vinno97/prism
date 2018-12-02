#include "World/Assemblers/CliffCornerAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffCornerComponent.h"

using namespace World;
using namespace World::Assemblers;

void CliffCornerAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == TODO) {
		EntityFactory().createCliffCorner(entity, entityManager, 180);
	}
	else if (worldObject.gid == TODO) {
		EntityFactory().createCliffCorner(entity, entityManager, 90);
	}
	else if (worldObject.gid == TODO) {
		EntityFactory().createCliffCorner(entity, entityManager, 0);
	}
	else if (worldObject.gid == TODO) {
		EntityFactory().createCliffCorner(entity, entityManager, 270);
	}
}

void CliffCornerAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::CliffCornerComponent>(entity)) {
		worldObject.gid = TODO;
	}
}