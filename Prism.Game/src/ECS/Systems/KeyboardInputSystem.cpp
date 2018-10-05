#pragma once

#include "Context.h"
#include "InputManager.h"

#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

namespace ECS {
	namespace Systems {
		KeyboardInputSystem::KeyboardInputSystem(EntityManager* entityManager) : System(entityManager) {
		}

		KeyboardInputSystem::~KeyboardInputSystem() {
			std::cout << typeid(this).name() << std::endl;
			//= default;
		}

		void KeyboardInputSystem::update(Context context) {
			auto input = context.inputManager;
			
			for (auto entity : entityManager->getAllEntitiesWithComponent<KeyboardInputComponent>()) {
				auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

				if (input->isKeyPressed(Key::KEY_W))
				{
					velocity->dx -= 1;
				}
				if (input->isKeyPressed(Key::KEY_S))
				{
					velocity->dx += 1;
				}
				if (input->isKeyPressed(Key::KEY_A))
				{
					velocity->dy -= 1;
				}
				if (input->isKeyPressed(Key::KEY_D))
				{
					velocity->dy += 1;
				}
			}

			
		}
	}
}