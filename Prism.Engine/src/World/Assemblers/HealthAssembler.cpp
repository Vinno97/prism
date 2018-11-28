#include "World/Assemblers/HealthAssembler.h"
#include "ECS/Components/HealthComponent.h"
#include <iostream>

using namespace ECS;
using namespace World;
using namespace ECS::Components;
using namespace World::Assemblers;

void HealthAssembler::assemble(int entity, const WorldObject& worldObject, ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<HealthComponent>(entity) && worldObject.additionalProperties.find("health") != worldObject.additionalProperties.end()) {
		const auto health = entityManager.getComponent<HealthComponent>(entity);
		health->health = std::stoi(worldObject.additionalProperties.at("health").value);
	}
}

void HealthAssembler::disassemble(int entity, WorldObject& worldObject, const ECS::EntityManager& entityManager) const {
	if (entityManager.hasComponent<HealthComponent>(entity)) {
		const auto health = entityManager.getComponent<HealthComponent>(entity);
		worldObject.additionalProperties["health"].value = std::to_string(health->health);
	}
}
