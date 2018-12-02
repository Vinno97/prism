#include "World/Assemblers/CliffAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffComponent.h"

using namespace World;
using namespace World::Assemblers;

void CliffAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == TODO) {
		EntityFactory().createCliff(entity, entityManager, 180);
	}	else if (worldObject.gid == TODO) {
		EntityFactory().createCliff(entity, entityManager, 90);
	}	else if (worldObject.gid == TODO) {
		EntityFactory().createCliff(entity, entityManager, 0);
	}	else if (worldObject.gid == TODO) {
		EntityFactory().createCliff(entity, entityManager, 270);
	}
}

void CliffAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::CliffComponent>(entity)) {
		worldObject.gid = TODO;
	}
}