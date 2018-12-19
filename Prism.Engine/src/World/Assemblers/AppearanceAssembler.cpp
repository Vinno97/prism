
#include "World/Assemblers/AppearanceAssembler.h"
#include "ECS/Components/AppearanceComponent.h"

using namespace ECS;
using namespace World;
using namespace ECS::Components;
using namespace World::Assemblers;

void AppearanceAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<AppearanceComponent>(entity)) {
		auto appearance = entityManager.getComponent<AppearanceComponent>(entity);
		//appearance->scaleX = worldObject.width;
		//appearance->scaleY = (worldObject.width + worldObject.height) / 2.f;
		//appearance->scaleZ = worldObject.height;

		appearance->scaleX *= worldObject.width;
		appearance->scaleY *= (worldObject.width + worldObject.height) / 2.f;
		appearance->scaleZ *= worldObject.height;
	}
}

void AppearanceAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	//if (entityManager.hasComponent<AppearanceComponent>(entity)) {
	//	auto appearance = entityManager.getComponent<AppearanceComponent>(entity);
	//	worldObject.width = appearance->scaleX;
	//	worldObject.height = appearance->scaleZ;
	//}
}
