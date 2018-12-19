#include "World/Assemblers/CliffCornerAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffCornerComponent.h"
#include "ECS/Components/AppearanceComponent.h"

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
		const auto appearance = entityManager.getComponent<ECS::Components::AppearanceComponent>(entity);
		if (appearance->rotationY == 0) {
			worldObject.gid = 13;
		} else if (appearance->rotationY  == 270) {
			worldObject.gid = 14;
		} else if (appearance->rotationY == 180) {
			worldObject.gid = 15;
		} else if (appearance->rotationY == 90) {
			worldObject.gid = 16;
		}
	}
}
