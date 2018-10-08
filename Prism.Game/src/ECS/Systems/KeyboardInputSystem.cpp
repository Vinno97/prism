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
			float speed = 1 / 10000.f;

			auto input = context.inputManager;

			for (auto entity : entityManager->getAllEntitiesWithComponent<KeyboardInputComponent>()) {
				auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

				if (input->isKeyPressed(Key::KEY_W))
				{
					velocity->dx -= speed * context.deltaTime;
				}
				if (input->isKeyPressed(Key::KEY_S))
				{
					velocity->dx += speed * context.deltaTime;
				}
				if (input->isKeyPressed(Key::KEY_A))
				{
					velocity->dy -= speed * context.deltaTime;
				}
				if (input->isKeyPressed(Key::KEY_D))
				{
					velocity->dy += speed * context.deltaTime;
				}
			}
		}
	}
}