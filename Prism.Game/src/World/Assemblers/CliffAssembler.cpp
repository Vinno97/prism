#include "World/Assemblers/CliffAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffComponent.h"

using namespace World;
using namespace World::Assemblers;

void CliffAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 9) {
		EntityFactory().createCliff(entity, entityManager);
	}
}

void CliffAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::CliffComponent>(entity)) {
		worldObject.gid = 9;
	}
}