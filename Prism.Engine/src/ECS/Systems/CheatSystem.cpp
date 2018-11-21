#include <math.h>
#include "ECS/Systems/AttackSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Systems/CheatSystem.h"

ECS::Systems::CheatSystem::CheatSystem(EntityManager &entityManager) : System(entityManager) { }

void ECS::Systems::CheatSystem::increaseHealth()
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
		auto healtComponent = entityManager->getComponent<HealthComponent>(entity.id);
		if (ticks == 0)
		{
			ticks = 1;;
			healtComponent->health += 100;
			//Test:
			//std::cout << healtComponent->health << std::endl;
		}
		else {
			ticks++;
			if (ticks == 2) {
				ticks = 0;
			}
		}
	}
}



ECS::Systems::CheatSystem::~CheatSystem()
{
}

void ECS::Systems::CheatSystem::update(Context context)
{
}

ECS::System * ECS::Systems::CheatSystem::clone()
{
	return nullptr;
}
