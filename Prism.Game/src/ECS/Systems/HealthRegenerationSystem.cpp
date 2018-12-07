#include "ECS/Systems/HealthRegenerationSystem.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/PlayerComponent.h"

using namespace ECS;
using namespace ECS::Systems;
using namespace ECS::Components;

ECS::Systems::HealthRegenerationSystem::HealthRegenerationSystem(EntityManager & entityManager) :System(entityManager) { }

ECS::Systems::HealthRegenerationSystem::~HealthRegenerationSystem()
{
}

void ECS::Systems::HealthRegenerationSystem::update(Context & context)
{
	if (deltaTime > 0) {
		deltaTime -= context.deltaTime;
	}
	for (auto & entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
		auto health = entityManager->getComponent<HealthComponent>(entity.id);
		std::cout << health->health <<std::endl;
		if (health != nullptr) {
			if (deltaTime <= 0 && health->health < 100) {
				health->health++;
				if (health->health > 100) {
					health->health = 100;
				}
				deltaTime = regenTime;
			}
		}
	}
}