#include "World/EntityConfigurators/AppearanceConfigurator.h"

#include "ECS/Components/ResourceSpawnComponent.h"

using namespace ECS;
using namespace ECS::Components;

namespace World {
	namespace EntityConfigurators {
		void AppearanceConfigurator::configure(int entity, const WorldObject &object, EntityManager& entityManager) const {
			if (entityManager.hasComponent<ResourceSpawnComponent>(entity) && object.additionalProperties.find("maximumStock") != object.additionalProperties.end()) {
				auto spawnpoint = entityManager.getComponent<ResourceSpawnComponent>(entity);

				spawnpoint->maximumStock = std::stoi(object.additionalProperties.at("maximumStock").value);

				spawnpoint->currentStock = spawnpoint->maximumStock;
				if (object.additionalProperties.find("hasCurrentStock") != object.additionalProperties.end()) {
					spawnpoint->currentStock = std::stoi(object.additionalProperties.at("hasCurrentStock").value);
				}
			}
		}
	}
}