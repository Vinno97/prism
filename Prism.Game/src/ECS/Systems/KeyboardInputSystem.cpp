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
#include "Math/Vector3f.h"

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
			
			float dirX = 0;
			float dirY = 0;


			for (auto entity : entityManager->getAllEntitiesWithComponent<KeyboardInputComponent>()) {
				auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);

				if (input->isKeyPressed(Key::KEY_W))
				{
					dirY -= acceleration;
				}
				if (input->isKeyPressed(Key::KEY_S))
				{
					dirY += acceleration;
				}
				if (input->isKeyPressed(Key::KEY_A))
				{
					dirX -= acceleration;
				}
				if (input->isKeyPressed(Key::KEY_D))
				{
					dirX += acceleration;
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
				
				Math::Vector3f v = Math::Vector3f(dirX, dirY, 0);
				v.normalize();
				velocity->dx += v.x * acceleration*context.deltaTime;
				velocity->dy += v.y * acceleration*context.deltaTime;
				
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

		std::unique_ptr<System> KeyboardInputSystem::clone()
		{
			return std::make_unique<KeyboardInputSystem>(*entityManager);
		}
	}
}