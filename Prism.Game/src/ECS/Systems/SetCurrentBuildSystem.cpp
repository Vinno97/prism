#include "ECS/Systems/SetCurrentBuildSystem.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/MousePointerComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/ShootingComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/DynamicComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/CollidableComponent.h"
#include "ECS/Components/BuildComponent.h"
#include "EntityFactory.h"

#include <algorithm>
#include <cmath>

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Enums;

ECS::Systems::SetCurrentBuildSystem::SetCurrentBuildSystem(EntityManager &entityManager) : System(entityManager) {
}

ECS::Systems::SetCurrentBuildSystem::~SetCurrentBuildSystem()
= default;


void ECS::Systems::SetCurrentBuildSystem::update(Context& context) {
	if (buildWaitTime > 0) {
		buildWaitTime -= context.deltaTime;
	}

	if (shootWaitTime > 0) {
		shootWaitTime -= context.deltaTime;
	}

	for (auto builder : entityManager->getAllEntitiesWithComponent<BuildComponent>()) {
		auto builderId = builder.id;
		auto &builderComponent = builder.component;

		if (buildWaitTime <= 0) {
			auto key1Pressed = context.inputManager->isKeyPressed(Key::KEY_1);
			auto key2Pressed = context.inputManager->isKeyPressed(Key::KEY_2);
			auto key3Pressed = context.inputManager->isKeyPressed(Key::KEY_3);
			auto keyTabPressed = context.inputManager->isKeyPressed(Key::KEY_TAB);

			if (key1Pressed || key2Pressed || key3Pressed || keyTabPressed) {
				buildWaitTime = waitTime;

				int tempBuildId = -1;

				if (builderComponent->isBuilding) {
					entityManager->removeEntity(builderComponent->buildingId);
					builderComponent->buildingId = -1;
				}

				if (key1Pressed && builderComponent->currentBuild != BuildTypes::WALL) {
					tempBuildId = EntityFactory::getInstance().createWall(*entityManager);
					builderComponent->currentBuild = BuildTypes::WALL;
					builderComponent->isBuilding = true;
				}
				else if (key2Pressed && builderComponent->currentBuild != BuildTypes::TOWER) {
					tempBuildId = EntityFactory::getInstance().createTower(*entityManager);
					builderComponent->currentBuild = BuildTypes::TOWER;
					builderComponent->isBuilding = true;
				}
				else if (key3Pressed && builderComponent->currentBuild != BuildTypes::MINE) {
					tempBuildId = EntityFactory::getInstance().createMine(*entityManager);
					builderComponent->currentBuild = BuildTypes::MINE;
					builderComponent->isBuilding = true;
				} 
				else{
					builderComponent->currentBuild = BuildTypes::NONE;
					builderComponent->isBuilding = false;
				}

				if (builderComponent->isBuilding) {
					auto appearance = entityManager->getComponent<AppearanceComponent>(tempBuildId);
					appearance->scaleX *= 1.1;
					appearance->scaleY *= 1.1;
					appearance->scaleZ *= 1.1;

					auto boundingBox = entityManager->getComponent<BoundingBoxComponent>(tempBuildId);
					auto position = entityManager->getComponent<PositionComponent>(tempBuildId);

					if (appearance != nullptr && boundingBox != nullptr && position != nullptr) {
						shootWaitTime = waitTime;
						builderComponent->isUsingMouse = true;

						builderComponent->buildingId = entityManager->createEntity(*appearance, *boundingBox, *position, DynamicComponent());
						entityManager->removeEntity(tempBuildId);
					}
					else
					{
						builderComponent->currentBuild = BuildTypes::NONE;
						builderComponent->isBuilding = false;
					}
				}
			}
		}
		if (shootWaitTime <= 0 && !builderComponent->isBuilding) {
			builderComponent->isUsingMouse = false;
		}
	}
}
