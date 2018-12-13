#include "World/Assemblers/AppearanceAssembler.h"
#include "ECS/Components/AppearanceComponent.h"

using namespace ECS;
using namespace World;
using namespace Components;
using namespace Assemblers;

void AppearanceAssembler::assemble(int entity, const WorldObject& worldObject, EntityManager& entityManager) const
{
	if (entityManager.hasComponent<AppearanceComponent>(entity))
	{
		auto appearance = entityManager.getComponent<AppearanceComponent>(entity);
		// TODO: Schakel deze code in zodra de modellen allemaal genormaliseerde groottes hebben. 
		//appearance->scaleX = worldObject.width;
		//appearance->scaleY = (worldObject.width + worldObject.height) / 2.f;
		//appearance->scaleZ = worldObject.height;

		appearance->scaleX *= worldObject.width;
		appearance->scaleY *= (worldObject.width + worldObject.height) / 2.f;
		appearance->scaleZ *= worldObject.height;
	}
}

void AppearanceAssembler::disassemble(int entity, WorldObject& worldObject, const EntityManager& entityManager) const
{
	// TODO: Schakel deze code in zodra de modellen allemaal genormaliseerde groottes hebben. 
	//if (entityManager.hasComponent<AppearanceComponent>(entity)) {
	//	auto appearance = entityManager.getComponent<AppearanceComponent>(entity);
	//	worldObject.width = appearance->scaleX;
	//	worldObject.height = appearance->scaleZ;
	//}
}
