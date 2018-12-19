#include "World/Assemblers/CliffAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/CliffComponent.h"
#include "ECS/Components/AppearanceComponent.h"

using namespace World;
using namespace World::Assemblers;

void CliffAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 9) {
		EntityFactory().createCliff(entity, entityManager, 0);
	}	else if (worldObject.gid == 10) {
		EntityFactory().createCliff(entity, entityManager, 270);
	}	else if (worldObject.gid == 11) {
		EntityFactory().createCliff(entity, entityManager, 180);
	}	else if (worldObject.gid == 12) {
		EntityFactory().createCliff(entity, entityManager, 90);
	}
}

void CliffAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::CliffComponent>(entity)) {
		const auto appearance = entityManager.getComponent<ECS::Components::AppearanceComponent>(entity);
		if (appearance->rotationY == 0) {
			worldObject.gid = 9;
		} else if (appearance->rotationY  == 270) {
			worldObject.gid = 10;
		} else if (appearance->rotationY == 180) {
			worldObject.gid = 11;
		} else if (appearance->rotationY == 90) {
			worldObject.gid = 12;
		}
	}
}
