#include "World/Assemblers/CliffFillerAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffFillerComponent.h"

using namespace World;
using namespace World::Assemblers;

void CliffFillerAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 19) {
		EntityFactory().createCliffFiller(entity, entityManager);
	}
}

void CliffFillerAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::CliffFillerComponent>(entity)) {
		worldObject.gid = 19;
	}
}