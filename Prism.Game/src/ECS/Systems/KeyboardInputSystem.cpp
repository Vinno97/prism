#pragma once

#include "Context.h"
#include "InputManager.h"

#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

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



		//	//TODO MOET WAARSCHIJNLIJK ANDERS
		//	if (input->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT))
		//	{
		//		auto position = entityManager->getComponent<PositionComponent>(entity.id);
		//		std::vector<int> pos = input->GetMousePoisiton();
		//		float x = (pos[0] - context.window->width / 2.0)*0.006;
		//		float y = (pos[1] - context.window->height / 2.0)*0.006;
		//		velocity->dx = -1 * (position->x - x);
		//		velocity->dy = -1 * (position->y - y);
		//		//position->x = x;
		//		//position->y = y;
		//	}


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
		System * KeyboardInputSystem::clone()
		{
			auto test = new KeyboardInputSystem(*entityManager);
			return test;
		}
	}
}