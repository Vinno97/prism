#include "ECS/Systems/BuildSystem.h"
#include "ECS/EntityManager.h";
#include "ECS/SystemManager.h";
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

ECS::Systems::BuildSystem::BuildSystem(EntityManager &entityManager, float wallRequirements, float towerRequirements, float mineRequirements) : System(entityManager) {
	this->wallRequirements = wallRequirements;
	this->towerRequirements = towerRequirements;
	this->mineRequirements = mineRequirements;
}

ECS::Systems::BuildSystem::~BuildSystem()
= default;


void ECS::Systems::BuildSystem::update(Context& context) {
	auto builderId = setCurrentBuild(context);
	placeCurrentBuild(context, builderId);
	moveCurrentBuilt();
}

int ECS::Systems::BuildSystem::setCurrentBuild(Context &context)
{
	auto builders = entityManager->getAllEntitiesWithComponent<BuildComponent>();
	if (builders.size() > 0) {
		auto &builder = builders[0];
		auto &builderComponent = builder.component;
		auto builderId = builder.id;

		if (buildDeltaTime > 0) {
			buildDeltaTime -= context.deltaTime;
		}

		if (shootDeltaTime > 0) {
			shootDeltaTime -= context.deltaTime;
		}

		if (buildDeltaTime <= 0) {
			auto key1Pressed = context.inputManager->isKeyPressed(Key::KEY_1);
			auto key2Pressed = context.inputManager->isKeyPressed(Key::KEY_2);
			auto key3Pressed = context.inputManager->isKeyPressed(Key::KEY_3);
			auto keyTabPressed = context.inputManager->isKeyPressed(Key::KEY_TAB);

			if (key1Pressed || key2Pressed || key3Pressed || keyTabPressed) {
				buildDeltaTime = waitTime;
				int tempBuildId = -1;

				if (currentBuild != BuildingType::NONE) {
					entityManager->removeEntity(buildingId);
					buildingId = -1;
					builderComponent->isBuilding = false;
				}

				if (key1Pressed && currentBuild != BuildingType::WALL) {
					tempBuildId = ef.createWall(*entityManager);
					currentBuild = BuildingType::WALL;
					builderComponent->isBuilding = true;
				}
				else if (key2Pressed && currentBuild != BuildingType::TOWER) {
					tempBuildId = ef.createTower(*entityManager);
					currentBuild = BuildingType::TOWER;
					builderComponent->isBuilding = true;
				}
				else if (key3Pressed && currentBuild != BuildingType::MINE) {
					tempBuildId = ef.createMine(*entityManager);
					currentBuild = BuildingType::MINE;
					builderComponent->isBuilding = true;
				}
				else {
					currentBuild = BuildingType::NONE;
					builderComponent->isBuilding = false;
				}

				if (currentBuild != BuildingType::NONE) {
					auto appearance = entityManager->getComponent<AppearanceComponent>(tempBuildId);
					auto boundingBox = entityManager->getComponent<BoundingBoxComponent>(tempBuildId);
					auto position = entityManager->getComponent<PositionComponent>(tempBuildId);

					if (appearance != nullptr && boundingBox != nullptr && position != nullptr) {
						buildingId = entityManager->createEntity(*appearance, *boundingBox, *position, DynamicComponent());
						buildingColor = appearance->color;
						buildingScaleX = appearance->scaleX;
						buildingScaleY = appearance->scaleY;
						buildingScaleZ = appearance->scaleZ;
						entityManager->removeEntity(tempBuildId);
					}
					else
					{
						currentBuild = BuildingType::NONE;
					}
				}
			}
		}
		return builderId;
	}
	return -1;
}

void ECS::Systems::BuildSystem::placeCurrentBuild(Context &context, unsigned int builderId)
{
	if (currentBuild != BuildingType::NONE) {
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(buildingId);
		auto inventory = entityManager->getComponent<InventoryComponent>(builderId);

		if (inventory != nullptr) {
			bool enoughResources = false;
			if (currentBuild == BuildingType::WALL && inventory->greenResource >= wallRequirements) {
				enoughResources = true;
			}
			else if (currentBuild == BuildingType::TOWER && inventory->redResource >= towerRequirements) {
				enoughResources = true;
			}
			else if (currentBuild == BuildingType::MINE && inventory->blueResource >= towerRequirements) {
				enoughResources = true;
			}

			bool canPlace = !boundingBoxComponent->didCollide;

			auto appearance = entityManager->getComponent<AppearanceComponent>(buildingId);
			appearance->color = buildingColor;
			appearance->scaleX = buildingScaleX;
			appearance->scaleY = buildingScaleY;
			appearance->scaleZ = buildingScaleZ;

			auto shooting = entityManager->getComponent<ShootingComponent>(builderId);
			shooting->isShooting = false;

			if (canPlace && enoughResources) {
				if (context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {
					unsigned int tempId;
					if (currentBuild == BuildingType::WALL) {
						tempId = ef.createWall(*entityManager);
						inventory->greenResource -= wallRequirements;
						shootDeltaTime = waitTime;
					}
					else if (currentBuild == BuildingType::TOWER) {
						tempId = ef.createTower(*entityManager);
						inventory->redResource -= towerRequirements;
						shootDeltaTime = waitTime;
					}
					else if (currentBuild == BuildingType::MINE) {
						tempId = ef.createMine(*entityManager);
						inventory->blueResource -= mineRequirements;
						shootDeltaTime = waitTime;
					}
					auto position = entityManager->getComponent<PositionComponent>(tempId);
					if (position != nullptr) {
						position->x = posX;
						position->y = posY;
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
				appearance->scaleX = buildingScaleX * 1.1;
				appearance->scaleY = buildingScaleY * 1.1;
				appearance->scaleZ = buildingScaleZ * 1.1;
			}
			boundingBoxComponent->didCollide = false;
		}
	}
}

void ECS::Systems::BuildSystem::moveCurrentBuilt()
{
	if (currentBuild != BuildingType::NONE) {
		auto entities = entityManager->getAllEntitiesWithComponent<MousePointerComponent>();
		if (entities.size() > 0) {
			auto entityId = entities[0].id;
			auto mousePosition3D = entityManager->getComponent<ECS::Components::PositionComponent>(entityId);
			auto buildingPosition = entityManager->getComponent<PositionComponent>(buildingId);
			buildingPosition->x = posX = std::ceil(mousePosition3D->x);
			buildingPosition->y = posY = std::ceil(mousePosition3D->y);
		}
	}
}
