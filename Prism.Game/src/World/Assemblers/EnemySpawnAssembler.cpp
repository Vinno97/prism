#include "World/Assemblers/EnemySpawnAssembler.h"
#include "EntityFactory.h"
#include "ECS/Components/EnemySpawnComponent.h"

using namespace World;
using namespace World::Assemblers;

void EnemySpawnAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (worldObject.gid == 20) {

		float spawnInterval = 10;
		bool enabled = true;

		if (worldObject.additionalProperties.find("spawnInterval") != worldObject.additionalProperties.end()) {
			spawnInterval = std::stoi(worldObject.additionalProperties.at("spawnInterval").value);
		}

		if (worldObject.additionalProperties.find("enabled") != worldObject.additionalProperties.end()) {
			enabled = std::stoi(worldObject.additionalProperties.at("enabled").value);
		}

		EntityFactory().createEnemySpawn(entity, entityManager, spawnInterval, enabled);
	}
}

void EnemySpawnAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<ECS::Components::EnemySpawnComponent>(entity)) {
		worldObject.gid = 20;
		auto enemySpawnComponent = entityManager.getComponent<ECS::Components::EnemySpawnComponent>(entity);

		worldObject.additionalProperties["spawnInterval"] = ObjectProperties("spawnInterval", std::to_string(enemySpawnComponent->spawnInterval));
		worldObject.additionalProperties["enabled"] = ObjectProperties("enabled", std::to_string(enemySpawnComponent->enabled));
	}
}
