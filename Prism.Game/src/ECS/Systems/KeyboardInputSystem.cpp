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
#include "ECS/Components/AccelerationComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "Math/Vector2.h"

namespace ECS {
	namespace Systems {
		using namespace Components;
		
		KeyboardInputSystem::KeyboardInputSystem(EntityManager &entityManager) : System(entityManager) {
		}

		KeyboardInputSystem::~KeyboardInputSystem()
			= default;

		void KeyboardInputSystem::update(Context& context) {
			auto input = context.inputManager;

			for (auto entity : entityManager->getAllEntitiesWithComponent<KeyboardInputComponent>()) {
				auto velocity = entityManager->getComponent<VelocityComponent>(entity.id);
				auto acceleration = entityManager->getComponent<AccelerationComponent>(entity.id)->force;
				Math::Vector2d direction;

				if (input->isKeyPressed(Key::KEY_W))
				{
					direction.y -= 1;
				}
				if (input->isKeyPressed(Key::KEY_S))
				{
					direction.y += 1;
				}
				if (input->isKeyPressed(Key::KEY_A))
				{
					direction.x -= 1;
				}
				if (input->isKeyPressed(Key::KEY_D))
				{
					direction.x += 1;
				}

				direction.normalize();
				velocity->dx += direction.x * acceleration*context.deltaTime;
				velocity->dy += direction.y * acceleration*context.deltaTime;

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
