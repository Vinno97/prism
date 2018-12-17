#include "ECS/Systems/ShootingSystem.h"
#include "ECS/Components/ShootingComponent.h"
#include "EntityFactory.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/BulletComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/PointLightComponent.h"

using namespace ECS::Components;

namespace ECS {
	namespace Systems {
		ShootingSystem::ShootingSystem(EntityManager& entityManager) : System(entityManager)
		{
		}


		ShootingSystem::~ShootingSystem()
			= default;

		void ShootingSystem::update(Context& context)
		{
			for (auto entity : entityManager->getAllEntitiesWithComponent<ShootingComponent>()) {
				auto component = entityManager->getComponent<ShootingComponent>(entity.id);
				pastTime += context.deltaTime;
				if (component->isShooting && pastTime > cooldown) {
					pastTime = 0;
					int projectileId = EntityFactory::getInstance().createProjectile(*entityManager);
					auto position = entityManager->getComponent<PositionComponent>(projectileId);
					position->x = entityManager->getComponent<PositionComponent>(entity.id)->x + (component->xdirection / 4);
					position->y = entityManager->getComponent<PositionComponent>(entity.id)->y + (component->ydirection / 4);

					auto velocity = entityManager->getComponent<VelocityComponent>(projectileId);
					auto pointLight = entityManager->getComponent<PointLightComponent>(projectileId);
					velocity->dx = component->xdirection * 5;
					velocity->dy = component->ydirection * 5;

					if (entityManager->hasComponent<AppearanceComponent>(entity.id)) {
						auto entityAppearance = entityManager->getComponent<AppearanceComponent>(entity.id);
						auto projectileAppearance = entityManager->getComponent<AppearanceComponent>(projectileId);
						auto projectilePosition = entityManager->getComponent<PositionComponent>(projectileId);
						if (component->shotByTower) {
							projectilePosition->z = 1;
						}
						projectileAppearance->color = entityAppearance->color;
						pointLight->color = Math::Vector3f(entityAppearance->color.x, entityAppearance->color.y, entityAppearance->color.z);
						context.audioManager->playSound("Bullet", 0);
					}
					entityManager->getComponent<BulletComponent>(projectileId)->lifeTime = 2;
					component->isShooting = false;
				}
			}

			for (auto entity : entityManager->getAllEntitiesWithComponent<BulletComponent>()) {
				auto component = entityManager->getComponent<BulletComponent>(entity.id);
				if (component->lifeTime < 0.0f) {
					entityManager->removeEntity(entity.id);
				}
				else {
					component->lifeTime -= context.deltaTime;
				}
			}

		}
	}
}
