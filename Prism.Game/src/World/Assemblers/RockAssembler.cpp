#include "World/Assemblers/RockAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/RockComponent.h"

using namespace World;
using namespace World::Assemblers;

void RockAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 11) {
		EntityFactory().createRock(entity, entityManager);
	}
}

void RockAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::RockComponent>(entity)) {
		worldObject.gid = 11;
	}
}