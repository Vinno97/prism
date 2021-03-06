#include "ECS/Systems/AimingSystem.h"
#include "ECS/Components/ShootingComponent.h"
#include "ECS/Components/MousePointerComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/BuildComponent.h"
#include <math.h>
#include "ECS/Components/PositionComponent.h"

using namespace ECS;
using namespace Systems;
using namespace Components;

namespace ECS {
	namespace Systems {
		using namespace Components;

		AimingSystem::AimingSystem(EntityManager& entityManager) : System(entityManager)
		{
		}


		AimingSystem::~AimingSystem()
			= default;

		void AimingSystem::update(Context& context)
		{
			auto input = context.inputManager;
			for (auto player : entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
				auto buildComponent = entityManager->getComponent<BuildComponent>(player.id);
				bool canShoot = true;
				if (buildComponent != nullptr) {
					if (buildComponent->isUsingMouse) {
						canShoot = false;
					}
				}
				if(canShoot){
					if (entityManager->hasComponent<PositionComponent>(player.id) && entityManager->hasComponent<ShootingComponent>(player.id)) {
						auto playerPosition = entityManager->getComponent<PositionComponent>(player.id);
						auto playerShooting = entityManager->getComponent<ShootingComponent>(player.id);
						playerShooting->shotByTower = false;
						if (input->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {
							for (auto entity : entityManager->getAllEntitiesWithComponent<MousePointerComponent>()) {
								auto component = entityManager->getComponent<PositionComponent>(entity.id);
								float xDif = component->x - playerPosition->x;
								float yDif = component->y - playerPosition->y;

								float pythagoras = sqrt((xDif * xDif) + (yDif * yDif));
								float normalizedX = xDif / pythagoras;
								float normalizedY = yDif / pythagoras;
								float spread = static_cast<float>((rand() % (10) - 5) / 100.0);
								playerShooting->xdirection = normalizedX + spread;
								playerShooting->ydirection = normalizedY + spread;
								playerShooting->isShooting = true;
							}
						}
						else {
							playerShooting->isShooting = false;
						}
					}
				}
			}
		}
	}
}
