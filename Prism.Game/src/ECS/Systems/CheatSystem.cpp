#include <math.h>
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Systems/CheatSystem.h"



namespace ECS {
	namespace Systems {
		using namespace Components;


		CheatSystem::CheatSystem(EntityManager &entityManager) : System(entityManager) { }


		void CheatSystem::increaseHealth()
		{
			for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
				auto healthComponent = entityManager->getComponent<HealthComponent>(entity.id);
				if (ticks == 0)
				{
					ticks = 1;;
					healthComponent->currentHealth += 100;
				}
				else {
					ticks++;
					if (ticks == 2) {
						ticks = 0;
					}
				}
			}
		}

		void CheatSystem::decreaseHealth()
		{
			for (auto entity : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
				auto healthComponent = entityManager->getComponent<HealthComponent>(entity.id);
				if (ticks == 0)
				{
					if (healthComponent->currentHealth <= 100) {
						healthComponent->currentHealth = 0;


					}
					else {
						healthComponent->currentHealth -= 100;
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

		void CheatSystem::increaseResources()
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

		void CheatSystem::decreaseResources()
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

		void CheatSystem::decreaseGameSpeed()
		{
			if (multiplier > 0.2) {
				multiplier -= 0.1;
			}

		}

		void CheatSystem::increaseGameSpeed()
		{
			if (multiplier < 2.5) {
				multiplier += 0.1;
			}

		}
		void CheatSystem::resetGameSpeed() {
			multiplier = 1.0;
		}

		CheatSystem::~CheatSystem()
		{
		}

		void CheatSystem::update(Context& context)
		{
			context.deltaTime *= multiplier;

			auto& input = context.inputManager;

			// TODO: Later naar in game buttons
			if (input->isKeyPressed(Key::KEY_H))
			{
				increaseHealth();
			}
			else if (input->isKeyPressed(Key::KEY_J)) {
				decreaseHealth();
			}
			else if (input->isKeyPressed(Key::KEY_R)) {
				increaseResources();
			}
			else if (input->isKeyPressed(Key::KEY_T)) {
				decreaseResources();
			}
			else if (input->isKeyPressed(Key::KEY_PLUS)) {
				increaseGameSpeed();
			}
			else if (input->isKeyPressed(Key::KEY_MIN)) {
				decreaseGameSpeed();
			}
			else if (input->isKeyPressed(Key::KEY_END)) {
				resetGameSpeed();
			}
		}

	}
}

