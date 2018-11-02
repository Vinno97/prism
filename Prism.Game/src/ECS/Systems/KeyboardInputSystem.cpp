#pragma once

#include "Context.h"
#include "InputManager.h"

#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

namespace ECS {
	namespace Systems {
		KeyboardInputSystem::KeyboardInputSystem(std::shared_ptr<EntityManager> entityManager) : System(entityManager) {
		}

		KeyboardInputSystem::~KeyboardInputSystem()
			= default;

		void KeyboardInputSystem::update(Context context) {
			// 1 unit/second^2
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
			}
		}
	}
}