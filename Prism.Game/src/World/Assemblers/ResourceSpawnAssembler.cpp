#include "World/Assemblers/ResourceSpawnAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/ResourceSpawnComponent.h"

using namespace World;
using namespace World::Assemblers;

World::Assemblers::ResourceSpawnAssembler::ResourceSpawnAssembler()
{
	resourceTypes[1] = Enums::ResourceType::RED;
	resourceTypes[2] = Enums::ResourceType::BLUE;
	resourceTypes[3] = Enums::ResourceType::GREEN;
}

void ResourceSpawnAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 2 || worldObject.gid == 11 || worldObject.gid == 13) {
		// TODO: Creëer het juiste type zodra dit in de game zit.

		auto value = 1;
		auto resourceType = Enums::ResourceType::BLUE;
		auto gatherRate = 1;

		resourceType = resourceTypes.at(worldObject.gid);

		if (worldObject.additionalProperties.find("gatherRate") != worldObject.additionalProperties.end()) {
			gatherRate = std::stoi(worldObject.additionalProperties.at("gatherRate").value);
		}
		if (worldObject.additionalProperties.find("value") != worldObject.additionalProperties.end()) {
			value = std::stoi(worldObject.additionalProperties.at("value").value);
		}
		
		EntityFactory().createResourcePoint(entity, entityManager, resourceType, gatherRate, value);
	}

}

void ResourceSpawnAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::ResourceSpawnComponent>(entity)) {
		auto resouceSpawnComponent = entityManager.getComponent<ECS::Components::ResourceSpawnComponent>(entity);
		
		for (const auto& typeMap : resourceTypes) {
			if (typeMap.second == resouceSpawnComponent->resourceType) worldObject.gid = typeMap.first;
		}

		worldObject.additionalProperties["value"] = ObjectProperties("value", std::to_string(resouceSpawnComponent->value));
		worldObject.additionalProperties["gatherRate"] = ObjectProperties("gatherRate", std::to_string(resouceSpawnComponent->SpawnTimer));
	}
}
