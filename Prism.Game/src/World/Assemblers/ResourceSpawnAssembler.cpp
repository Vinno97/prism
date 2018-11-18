#include "World/Assemblers/ResourceSpawnAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/ResourceSpawnComponent.h"

using namespace World;
using namespace World::Assemblers;

World::Assemblers::ResourceSpawnAssembler::ResourceSpawnAssembler()
{
	resourceTypes["blue"] = Enums::ResourceType::BLUE;
	resourceTypes["red"] = Enums::ResourceType::RED;
	resourceTypes["green"] = Enums::ResourceType::GREEN;
}

void ResourceSpawnAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 1 || worldObject.gid == 2 || worldObject.gid == 3) {
		// TODO: Creëer het juiste type zodra dit in de game zit.

		auto value = 1;
		auto resourceType = Enums::ResourceType::BLUE;
		auto gatherRate = 1;

		if (worldObject.additionalProperties.find("gatherRate") != worldObject.additionalProperties.end()) {
			gatherRate = std::stoi(worldObject.additionalProperties.at("gatherRate").value);
		}
		if (worldObject.additionalProperties.find("resourceType") != worldObject.additionalProperties.end()) {
			resourceType = resourceTypes.at(worldObject.additionalProperties.at("resourceType").value);
		}
		if (worldObject.additionalProperties.find("value") != worldObject.additionalProperties.end()) {
			value = std::stoi(worldObject.additionalProperties.at("value").value);
		}
		
		EntityFactory().createResourcePoint(entity, entityManager, resourceType, gatherRate, value);
	}

}

void ResourceSpawnAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::ResourceSpawnComponent>(entity)) {
		// TODO: Sla het juist type op zodra deze in de game zitten.
		auto resouceSpawnComponent = entityManager.getComponent<ECS::Components::ResourceSpawnComponent>(entity);
		worldObject.gid = 1;


		std::string temp = "";
		if (resouceSpawnComponent->resourceType == Enums::ResourceType::BLUE) {
			temp = "blue";
		}
		if (resouceSpawnComponent->resourceType == Enums::ResourceType::RED) {
			temp = "red";
		}
		if (resouceSpawnComponent->resourceType == Enums::ResourceType::GREEN) {
			temp = "green";
		}
		ObjectProperties type = ObjectProperties("resourceType", temp);
		worldObject.additionalProperties["resourceType"] = type;
		ObjectProperties value = ObjectProperties("value", std::to_string(resouceSpawnComponent->value));
		ObjectProperties gatherRate = ObjectProperties("gatherRate", std::to_string(resouceSpawnComponent->SpawnTimer));

		worldObject.additionalProperties["value"] = value;
		worldObject.additionalProperties["gatherRate"] = gatherRate;
	}
}
