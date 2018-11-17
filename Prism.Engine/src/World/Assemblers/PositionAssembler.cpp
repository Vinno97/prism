
#include "World/Assemblers/PositionAssembler.h"
#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace World;
using namespace ECS::Components;
using namespace World::Assemblers;

void PositionAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<PositionComponent>(entity)) {
		auto position = entityManager.getComponent<PositionComponent>(entity);
		position->x = worldObject.x;
		position->y = worldObject.y;
	}
}

void PositionAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<PositionComponent>(entity)) {
		auto position = entityManager.getComponent<PositionComponent>(entity);
		worldObject.x = position->x;
		worldObject.y = position->y;
	}
}
