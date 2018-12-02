#include "World/Assemblers/CliffAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffComponent.h"

using namespace World;
using namespace World::Assemblers;

void CliffAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 15) {
		EntityFactory().createCliff(entity, entityManager, 180);
	}	else if (worldObject.gid == 16) {
		EntityFactory().createCliff(entity, entityManager, 90);
	}	else if (worldObject.gid == 18) {
		EntityFactory().createCliff(entity, entityManager, 0);
	}	else if (worldObject.gid == 17) {
		EntityFactory().createCliff(entity, entityManager, 270);
	}
}

void CliffAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::CliffComponent>(entity)) {
		worldObject.gid = 15;
		worldObject.gid = 16;
		worldObject.gid = 17;
		worldObject.gid = 18;
	}
}