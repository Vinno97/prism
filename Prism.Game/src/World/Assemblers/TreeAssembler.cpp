#include "World/Assemblers/TreeAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/TreeComponent.h"

using namespace World;
using namespace World::Assemblers;

void TreeAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 17) {
		EntityFactory().createTree(entity, entityManager);
	}
}

void TreeAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::TreeComponent>(entity)) {
		worldObject.gid = 17;
	}
}