#include "ECS/Systems/BuildSystem.h"
#include "ECS/EntityManager.h";
#include "ECS/SystemManager.h";
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/BoundingBoxComponent.h"
#include "ECS/Components/MousePointerComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ShootingComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/DynamicComponent.h"
#include "ECS/Components/InventoryComponent.h"
#include "ECS/Components/PlacableComponent.h"
#include <algorithm>


ECS::Systems::BuildSystem::BuildSystem(EntityManager &entityManager) : System(entityManager) { }

ECS::Systems::BuildSystem::~BuildSystem()
= default;


void ECS::Systems::BuildSystem::update(Context& context) {

	deltaTime += context.deltaTime;
	auto playerId = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0].id;

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

			if (key1Pressed && currentBuild!=BuildingType::WALL) {
				buildingId = buildEntity(BuildingType::WALL);
				currentBuild = BuildingType::WALL;
				buildingColor = entityManager->getComponent<AppearanceComponent>(buildingId)->color;
			}
			else if (key2Pressed && currentBuild != BuildingType::TOWER) {
				buildingId = buildEntity(BuildingType::TOWER);
				currentBuild = BuildingType::TOWER;
				buildingColor = entityManager->getComponent<AppearanceComponent>(buildingId)->color;
			}
			else if (key3Pressed && currentBuild != BuildingType::FACTORY) {
				buildingId = buildEntity(BuildingType::FACTORY);
				currentBuild = BuildingType::FACTORY;
				buildingColor = entityManager->getComponent<AppearanceComponent>(buildingId)->color;
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
		else if (currentBuild == BuildingType::FACTORY && inventory->blueResource >= towerRequirements) {
			enoughResources = true;
		}
		
		bool canPlace = !boundingBoxComponent->didCollide;
		boundingBoxComponent->didCollide = false;
		auto appearance = entityManager->getComponent<AppearanceComponent>(buildingId);
		appearance->color = buildingColor;
		auto shooting = entityManager->getComponent<ShootingComponent>(playerId);
		shooting->isShooting = false;
		
		if (canPlace && enoughResources) {
			if (context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {
				currentBuild = BuildingType::NONE;
				entityManager->addComponentToEntity(buildingId, PlacableComponent());
				entityManager->removeComponentFromEntity<DynamicComponent>(buildingId);
				entityManager->removeComponentFromEntity<VelocityComponent>(buildingId);
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
		}
	}

	if (currentBuild != BuildingType::NONE) {
		auto entities = entityManager->getAllEntitiesWithComponent<MousePointerComponent>();
		if (entities.size() > 0) {
			auto entityId = entities[0].id;
			auto mousePosition3D = entityManager->getComponent<PositionComponent>(entityId);
			auto buildingPosition = entityManager->getComponent<PositionComponent>(buildingId);
			buildingPosition->x = (int)mousePosition3D->x;
			buildingPosition->y = (int)mousePosition3D->y;
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
	case ECS::Systems::BuildSystem::FACTORY:
		//TODO :: vervang FACTORY
		newBuildingId = ef.createEnemy(*entityManager);
		break;
	default:
		break;
	}

	if (buildingType != BuildingType::NONE) {
		if (!entityManager->hasComponent<DynamicComponent>(newBuildingId)) {
			entityManager->addComponentToEntity(newBuildingId, VelocityComponent());
			entityManager->addComponentToEntity(newBuildingId, DynamicComponent());
		}
		if (entityManager->hasComponent<PlacableComponent>(newBuildingId)) {
			entityManager->removeComponentFromEntity<PlacableComponent>(newBuildingId);
		}
	}
	return newBuildingId;
}
