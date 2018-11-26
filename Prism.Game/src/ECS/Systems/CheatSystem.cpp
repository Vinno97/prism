#include <math.h>
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Systems/CheatSystem.h"

ECS::Systems::CheatSystem::CheatSystem(EntityManager &entityManager) : System(entityManager) { }

void ECS::Systems::CheatSystem::increaseHealth()
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
		auto healthComponent = entityManager->getComponent<HealthComponent>(entity.id);
		if (ticks == 0)
		{
			ticks = 1;;
			healthComponent->health += 100;
			//Test:
			//std::cout << healthComponent->health << std::endl;
		}
		else {
			ticks++;
			if (ticks == 2) {
				ticks = 0;
			}
		}
	}
}

void ECS::Systems::CheatSystem::decreaseHealth()
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
		auto healthComponent = entityManager->getComponent<HealthComponent>(entity.id);
		if (ticks == 0)
		{
			if (healthComponent->health <= 100) {	
				healthComponent->health = 0;

				
			}
			else {
				healthComponent->health -= 100;
			}

			ticks = 1;
		}
		else {
			ticks++;
			if (ticks == 2) {
				ticks = 0;
			}
		}
	}
}

void ECS::Systems::CheatSystem::increaseResources()
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
		auto resources = entityManager->getComponent<InventoryComponent>(entity.id);
		if (ticks == 0)
		{
			ticks = 1;;
			resources->blueResource += 100;
			resources->redResource += 100;
			resources->greenResource += 100;
			
			//Test:
			std::cout << "Resources" << std::endl;
			std::cout << resources->blueResource << std::endl;
			std::cout << resources->redResource << std::endl;
			std::cout << resources->greenResource << std::endl;
		}
		else {
			ticks++;
			if (ticks == 2) {
				ticks = 0;
			}
		}
	}
}

void ECS::Systems::CheatSystem::decreaseResources()
{
	for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
		auto resources = entityManager->getComponent<InventoryComponent>(entity.id);
		if (ticks == 0)
		{
			ticks = 1;

			if (resources->blueResource <= 100) {
				resources->blueResource = 0;
			}
			else {
				resources->blueResource -= 100;
			}
			
			if (resources->redResource <= 100) {
				resources->redResource = 0;
			}
			else {
				resources->redResource -= 100;
			}

			if (resources->greenResource <= 100) {
				resources->greenResource = 0;
			}
			else {
				resources->greenResource -= 100;
			}

			//Test:
			std::cout << "Resources" << std::endl;
			std::cout << resources->blueResource << std::endl;
			std::cout << resources->redResource << std::endl;
			std::cout << resources->greenResource << std::endl;
		}
		else {
			ticks++;
			if (ticks == 2) {
				ticks = 0;
			}
		}
	}
}

void ECS::Systems::CheatSystem::decreaseGameSpeed()
{
	if (multiplier > 0.2) {
		multiplier -= 0.1;
	}
	
}

void ECS::Systems::CheatSystem::increaseGameSpeed()
{
	if (multiplier < 2.5) {
		multiplier += 0.1;
	}
	
}





ECS::Systems::CheatSystem::~CheatSystem()
{
}

void ECS::Systems::CheatSystem::update(Context& context)
{
	context.deltaTime *= multiplier;
}

ECS::System * ECS::Systems::CheatSystem::clone()
{
	return nullptr;
}
