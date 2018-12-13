#include "ECS/Systems/HealthRegenerationSystem.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include <cmath>

using namespace ECS;
using namespace Systems;
using namespace Components;

HealthRegenerationSystem::HealthRegenerationSystem(EntityManager& entityManager) : System(entityManager)
{
}

HealthRegenerationSystem::~HealthRegenerationSystem()
{
}

void HealthRegenerationSystem::update(Context& context)
{
	if (deltaTime > 0)
	{
		deltaTime -= context.deltaTime;
	}
	for (auto& entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>())
	{
		auto health = entityManager->getComponent<HealthComponent>(entity.id);
		if (health != nullptr)
		{
			if (deltaTime <= 0 && health->currentHealth < health->maxHealth)
			{
				health->currentHealth = std::ceil(health->currentHealth + context.deltaTime);
				if (health->currentHealth > health->maxHealth)
				{
					health->currentHealth = health->maxHealth;
				}
				deltaTime = regenTime;
			}
		}
	}
}
