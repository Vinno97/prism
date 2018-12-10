#include "ECS/Systems/PlaceCurrentBuildSystem.h"
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
#include <algorithm>
#include <cmath>

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Enums;

ECS::Systems::PlaceCurrentBuildSystem::PlaceCurrentBuildSystem(EntityManager &entityManager, float wallRequirements, float towerRequirements, float mineRequirements) : System(entityManager) {
	this->wallRequirements = wallRequirements;
	this->towerRequirements = towerRequirements;
	this->mineRequirements = mineRequirements;
}

ECS::Systems::PlaceCurrentBuildSystem::~PlaceCurrentBuildSystem()
= default;


void ECS::Systems::PlaceCurrentBuildSystem::update(Context& context) {
	if (shootDeltaTime > 0) {
		shootDeltaTime -= context.deltaTime;
	}

	for (auto builder : entityManager->getAllEntitiesWithComponent<BuildComponent>()) {
		auto builderId = builder.id;
		auto &builderComponent = builder.component;

		if (builderComponent->isBuilding) {
			auto builderPosition = entityManager->getComponent<PositionComponent>(builderId);

			auto x = (*builderComponent).posX;
			auto y = (*builderComponent).posY;

			auto xDistance = std::abs(x - builderPosition->x);
			auto yDistance = std::abs(y - builderPosition->y);

			bool inRange = true;
			auto appearance = entityManager->getComponent<AppearanceComponent>(builderComponent->buildingId);
			if (appearance != nullptr && std::sqrt((xDistance*xDistance) + (yDistance*yDistance)) > buildRange) {
				inRange = false;
			}

			auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(builderComponent->buildingId);
			auto inventory = entityManager->getComponent<InventoryComponent>(builderId);

			if (inventory != nullptr) {
				bool enoughResources = false;
				if (builderComponent->currentBuild == BuildTypes::WALL && inventory->greenResource >= wallRequirements) {
					enoughResources = true;
				}
				else if (builderComponent->currentBuild == BuildTypes::TOWER && inventory->redResource >= towerRequirements) {
					enoughResources = true;
				}
				else if (builderComponent->currentBuild == BuildTypes::MINE && inventory->blueResource >= towerRequirements) {
					enoughResources = true;
				}

				bool canPlace = !boundingBoxComponent->didCollide;
				auto appearance = entityManager->getComponent<AppearanceComponent>(builderComponent->buildingId);

				if (canPlace && enoughResources && inRange) {
					appearance->color = builderComponent->buildingColor;
					appearance->scaleX = builderComponent->buildingScaleX;
					appearance->scaleY = builderComponent->buildingScaleY;
					appearance->scaleZ = builderComponent->buildingScaleZ;

					if (context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {
						unsigned int tempId;
						if (builderComponent->currentBuild == BuildTypes::WALL) {
							tempId = ef.createWall(*entityManager);
							inventory->greenResource -= wallRequirements;
							shootDeltaTime = waitTime;
						}
						else if (builderComponent->currentBuild == BuildTypes::TOWER) {
							tempId = ef.createTower(*entityManager);
							inventory->redResource -= towerRequirements;
							shootDeltaTime = waitTime;
						}
						else if (builderComponent->currentBuild == BuildTypes::MINE) {
							tempId = ef.createMine(*entityManager);
							inventory->blueResource -= mineRequirements;
							shootDeltaTime = waitTime;
						}
						auto position = entityManager->getComponent<PositionComponent>(tempId);
						if (position != nullptr) {
							position->x = builderComponent->posX;
							position->y = builderComponent->posY;
						}
					}
				}
				else {
					if (!canPlace) {
						//TODO :: leuk muziekje?
					}
					if (!enoughResources) {
						//TODO :: leuk muziekje?
					}
					appearance->color = Math::Vector3f{ 1.0f, 0.5f, 0.5f };
					appearance->scaleX = builderComponent->buildingScaleX * 1.1;
					appearance->scaleY = builderComponent->buildingScaleY * 1.1;
					appearance->scaleZ = builderComponent->buildingScaleZ * 1.1;
				}
			}
		}
	}
}