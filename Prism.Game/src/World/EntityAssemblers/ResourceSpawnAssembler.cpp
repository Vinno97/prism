#include "World/Assemblers/ResourceSpawnAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/ResourceSpawnComponent.h"

using namespace World;
using namespace World::Assemblers;

void ResourceSpawnAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 1 || worldObject.gid == 2 || worldObject.gid == 3) {
		EntityFactory().createResourcePoint(entity, entityManager);
		if (worldObject.additionalProperties.find("maximumStock") != worldObject.additionalProperties.end()) {
			auto spawnpoint = entityManager.getComponent<ECS::Components::ResourceSpawnComponent>(entity);

			spawnpoint->maximumStock = std::stoi(worldObject.additionalProperties.at("maximumStock").value);

			spawnpoint->currentStock = spawnpoint->maximumStock;
			if (worldObject.additionalProperties.find("hasCurrentStock") != worldObject.additionalProperties.end()) {
				spawnpoint->currentStock = std::stoi(worldObject.additionalProperties.at("hasCurrentStock").value);
			}
		}
	}
}

void ResourceSpawnAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::ResourceSpawnComponent>(entity)) {
		// TODO: Sla het juist type op.
		worldObject.gid = 1;
	}
}
