#include "Context.h"
#include "InputManager.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "Math/Vector3f.h"


namespace ECS {
	namespace Systems {
		using namespace Components;
		
		KeyboardInputSystem::KeyboardInputSystem(EntityManager &entityManager) : System(entityManager) {
		}

		KeyboardInputSystem::~KeyboardInputSystem()
			= default;

		void KeyboardInputSystem::update(Context& context) {
			// 1 unit/second^2
			//double acceleration = 10;
			double acceleration = 15;
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
				
				Math::Vector3f v = Math::Vector3f(dirX, dirY, 0);
				v.normalize();
				velocity->dx += v.x * acceleration*context.deltaTime;
				velocity->dy += v.y * acceleration*context.deltaTime;	
			}
		}
	}
}
