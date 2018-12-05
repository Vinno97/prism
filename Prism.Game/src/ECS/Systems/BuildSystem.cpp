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
#include "ECS/Components/PlacableComponent.h"
#include <algorithm>

using namespace ECS;
using namespace ECS::Components;
using namespace ECS::Systems;

ECS::Systems::BuildSystem::BuildSystem(EntityManager &entityManager) : System(entityManager) { }

ECS::Systems::BuildSystem::~BuildSystem()
= default;


void ECS::Systems::BuildSystem::update(Context& context) {

	deltaTime += context.deltaTime;
	auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();
	if (players.size() > 0) {
		auto playerId = players[0].id;

		if (deltaTime > pressTime) {
			auto key1Pressed = context.inputManager->isKeyPressed(Key::KEY_1);
			auto key2Pressed = context.inputManager->isKeyPressed(Key::KEY_2);
			auto key3Pressed = context.inputManager->isKeyPressed(Key::KEY_3);
			auto keyTabPressed = context.inputManager->isKeyPressed(Key::KEY_TAB);
			BuildingType newBuild;

			if (key1Pressed || key2Pressed || key3Pressed || keyTabPressed) {
				deltaTime = 0;
				if (currentBuild != BuildingType::NONE) {
					entityManager->removeEntity(buildingId);
					buildingId = -1;
				}

				if (key1Pressed && currentBuild != BuildingType::WALL) {
					buildingId = buildEntity(BuildingType::WALL);
					currentBuild = BuildingType::WALL;
				}
				else if (key2Pressed && currentBuild != BuildingType::TOWER) {
					buildingId = buildEntity(BuildingType::TOWER);
					currentBuild = BuildingType::TOWER;
				}
				else if (key3Pressed && currentBuild != BuildingType::MINE) {
					buildingId = buildEntity(BuildingType::MINE);
					currentBuild = BuildingType::MINE;
				}
				else {
					currentBuild = BuildingType::NONE;
				}
			}
		}

		auto iBuilding = currentBuild != BuildingType::NONE;

		if (currentBuild != BuildingType::NONE) {
			auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(buildingId);
			auto inventory = entityManager->getComponent<InventoryComponent>(playerId);

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
			appearance->scaleZ = buildingScaleZ;

			auto shooting = entityManager->getComponent<ShootingComponent>(playerId);
			shooting->isShooting = false;

			if (canPlace && enoughResources) {
				if (context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {
					entityManager->removeEntity(buildingId);
					if (currentBuild == BuildingType::WALL) {
						buildingId = ef.createWall(*entityManager);
					}
					else if (currentBuild == BuildingType::TOWER) {
						buildingId = ef.createTower(*entityManager);
					}
					else if (currentBuild == BuildingType::MINE) {
						buildingId = ef.createMine(*entityManager);
					}
					currentBuild = BuildingType::NONE;
					auto position = entityManager->getComponent<PositionComponent>(buildingId);
					position->x = posX;
					position->y = posY;
					buildingId = -1;
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
				appearance->scaleX = buildingScaleX * 1.001;
				appearance->scaleZ = buildingScaleZ * 1.001;
			}
			boundingBoxComponent->didCollide = false;
		}

		if (currentBuild != BuildingType::NONE) {
			auto entities = entityManager->getAllEntitiesWithComponent<MousePointerComponent>();
			if (entities.size() > 0) {
				auto entityId = entities[0].id;
				auto mousePosition3D = entityManager->getComponent<ECS::Components:: PositionComponent>(entityId);
				auto buildingPosition = entityManager->getComponent<PositionComponent>(buildingId);
				buildingPosition->x = posX = (int)mousePosition3D->x;
				buildingPosition->y = posY = (int)mousePosition3D->y;
			}
		}
	}
}

unsigned int ECS::Systems::BuildSystem::buildEntity(BuildingType buildingType)
{
	unsigned int newBuildingId;
	switch (buildingType)
	{
	case ECS::Systems::BuildSystem::WALL:
		newBuildingId = ef.createWall(*entityManager);
		break;
	case ECS::Systems::BuildSystem::TOWER:
		newBuildingId = ef.createTower(*entityManager);
		break;
	case ECS::Systems::BuildSystem::MINE:
		newBuildingId = ef.createMine(*entityManager);
		break;
	default:
		return -1;
	}

	auto appearance = entityManager->getComponent<AppearanceComponent>(newBuildingId);
	auto boundingBox = entityManager->getComponent<BoundingBoxComponent>(newBuildingId);
	auto position = entityManager->getComponent<PositionComponent>(newBuildingId);

	newBuildingId = entityManager->createEntity(*appearance, *boundingBox, *position);
	
	buildingColor = appearance->color;
	buildingScaleX = appearance->scaleX;
	buildingScaleZ = appearance->scaleZ;

	return newBuildingId;
}
