#pragma once
#include <thread>
#include "Context.h"
#include "InputManager.h"
#include <mutex>
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

namespace ECS {
	namespace Systems {
		KeyboardInputSystem::KeyboardInputSystem(EntityManager &entityManager) : System(entityManager) {
		}




		KeyboardInputSystem::~KeyboardInputSystem()
			= default;

		void KeyboardInputSystem::update(Context& context) {
			// 1 unit/second^2
			//double acceleration = 5;
			double acceleration = 5;

			auto input = context.inputManager;

			for (auto entity : entityManager->getAllEntitiesWithComponent<KeyboardInputComponent>()) {
				auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

				if (input->isKeyPressed(Key::KEY_W))
				{
					velocity->dy -= acceleration * context.deltaTime;
				}
				if (input->isKeyPressed(Key::KEY_S))
				{
					velocity->dy += acceleration * context.deltaTime;
				}
				if (input->isKeyPressed(Key::KEY_A))
				{
					velocity->dx -= acceleration * context.deltaTime;
				}
				if (input->isKeyPressed(Key::KEY_D))
				{
					velocity->dx += acceleration * context.deltaTime;
				}

				if (entityManager->hasComponent<AppearanceComponent>(entity.id)) {
					auto appearance = entityManager->getComponent<AppearanceComponent>(entity.id);
					if (input->isKeyPressed(Key::KEY_Q))
					{
						appearance->rotationY -= context.deltaTime * 50;
					}
					if (input->isKeyPressed(Key::KEY_E))
					{
						appearance->rotationY += context.deltaTime * 50;
					}
				}

				// Cheat option to increase health of the Player
				if (entityManager->hasComponent<PlayerComponent>(entity.id)) {
					auto healthComponent = entityManager->getComponent<HealthComponent>(entity.id);
			
					if (input->isKeyPressed(Key::KEY_H))
					{
						// healthComponent->increase();
					}
				}
			}
		}

		System * KeyboardInputSystem::clone()
		{
			auto test = new KeyboardInputSystem(*entityManager);
			return test;
		}
	}
}