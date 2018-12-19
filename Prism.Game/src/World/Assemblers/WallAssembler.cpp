#include "World/Assemblers/WallAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/WallComponent.h"

using namespace World;
using namespace World::Assemblers;

void WallAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 6) {
		EntityFactory::getInstance().createWall(entity, entityManager);
	}
}

void WallAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::WallComponent>(entity)) {
		worldObject.gid = 6;
	}
}
