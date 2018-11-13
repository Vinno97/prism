#pragma once

#include "Context.h"
#include "InputManager.h"

#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Components/ShootingComponent.h"

namespace ECS {
	namespace Systems {
		KeyboardInputSystem::KeyboardInputSystem(EntityManager &entityManager) : System(entityManager) {
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
				if (entityManager->hasComponent<ShootingComponent>(entity.id)) {
					auto component = entityManager->getComponent<ShootingComponent>(entity.id);
					if (input->isKeyPressed(Key::KEY_UP)) {
						component->isShooting = true;
						component->xdirection = 0;
						component->ydirection = -1;
					}
					if (input->isKeyPressed(Key::KEY_DOWN)) {
						component->isShooting = true;
						component->xdirection = 0;
						component->ydirection = 1;
					}
					if (input->isKeyPressed(Key::KEY_LEFT)) {
						component->isShooting = true;
						component->xdirection = -1;
						component->ydirection = 0;
					}
					if (input->isKeyPressed(Key::KEY_RIGHT)) {
						component->isShooting = true;
						component->xdirection = 1;
						component->ydirection = 0;
					}
					if (!input->isKeyPressed(Key::KEY_UP) && !input->isKeyPressed(Key::KEY_DOWN) && !input->isKeyPressed(Key::KEY_LEFT) && !input->isKeyPressed(Key::KEY_RIGHT)) {
						component->isShooting = false;
						component->xdirection = 0;
						component->ydirection = 0;
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