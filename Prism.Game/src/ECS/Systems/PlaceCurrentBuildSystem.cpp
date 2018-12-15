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
#include "ECS/Components/WallComponent.h"
#include "ECS/Components/TowerComponent.h"
#include "ECS/Components/MineComponent.h"
#include "EntityFactory.h"
#include <algorithm>
#include <cmath>

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;
using namespace Enums;

ECS::Systems::PlaceCurrentBuildSystem::PlaceCurrentBuildSystem(EntityManager &entityManager, float wallRequirements, float towerRequirements, float mineRequirements, float buildRange) : System(entityManager) {
	this->wallRequirements = wallRequirements;
	this->towerRequirements = towerRequirements;
	this->mineRequirements = mineRequirements;
	this->buildRange = buildRange;
}

ECS::Systems::PlaceCurrentBuildSystem::~PlaceCurrentBuildSystem()
= default;


void ECS::Systems::PlaceCurrentBuildSystem::update(Context& context) {

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
					appearance->color = canBuildColor;

					if (context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {
						unsigned int tempId;
						if (builderComponent->currentBuild == BuildTypes::WALL) {
							tempId = EntityFactory::getInstance().createWall(*entityManager);
							inventory->greenResource -= wallRequirements;
						}
						else if (builderComponent->currentBuild == BuildTypes::TOWER) {
							tempId = EntityFactory::getInstance().createTower(*entityManager);
							inventory->redResource -= towerRequirements;
						}
						else if (builderComponent->currentBuild == BuildTypes::MINE) {
							tempId = EntityFactory::getInstance().createMine(*entityManager);
							inventory->blueResource -= mineRequirements;
						}
						auto position = entityManager->getComponent<PositionComponent>(tempId);
						if (position != nullptr) {
							position->x = builderComponent->posX;
							position->y = builderComponent->posY;
						}
					}
				}
				else {
					appearance->color = CanNotBuildColor;
					if (!canPlace && inRange) {
						auto & colliders = boundingBoxComponent->collidesWith;
						auto it = std::find_if(colliders.begin(), colliders.end(),
							[&,this](unsigned int collider) -> bool { return this->isBuilding(collider); });
					
						if (it != colliders.end()) {
							appearance->color = CanRemoveBuildColor;
							if (context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_RIGHT)) {
								entityManager->removeEntity(*it);
							}
						}						
					}
				}
			}
		}
	}
}

bool ECS::Systems::PlaceCurrentBuildSystem::isBuilding(unsigned int id) const
{
	if (entityManager->getComponent<WallComponent>(id)) {
		return true;
	}else if (entityManager->getComponent<TowerComponent>(id)) {
		return true;
	}else if (entityManager->getComponent<MineComponent>(id)) {
		return true;
	}
	return false;
}
