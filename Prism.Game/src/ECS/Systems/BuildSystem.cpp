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
	auto playerId = setCurrentBuild(context);
	placeCurrentBuild(context,playerId);
	moveCurrentBuilt();
}

int ECS::Systems::BuildSystem::setCurrentBuild(Context &context)
{
	auto players = entityManager->getAllEntitiesWithComponent<PlayerComponent>();
	if (players.size() > 0) {
		auto &player = players[0];
		auto &playerComponent = player.component;
		auto playerId = player.id;

		if (deltaTime > 0) {
			deltaTime -= context.deltaTime;
		}

		if (deltaTime == 0) {
			auto key1Pressed = context.inputManager->isKeyPressed(Key::KEY_1);
			auto key2Pressed = context.inputManager->isKeyPressed(Key::KEY_2);
			auto key3Pressed = context.inputManager->isKeyPressed(Key::KEY_3);
			auto keyTabPressed = context.inputManager->isKeyPressed(Key::KEY_TAB);
			BuildingType newBuild;

			if (key1Pressed || key2Pressed || key3Pressed || keyTabPressed) {
				deltaTime = waitTime;
				int tempBuildId = -1;

				if (currentBuild != BuildingType::NONE) {
					entityManager->removeEntity(buildingId);
					buildingId = -1;
					playerComponent->isBuilding = false;
				}

				if (key1Pressed && currentBuild != BuildingType::WALL) {
					tempBuildId = ef.createWall(*entityManager);
					currentBuild = BuildingType::WALL;
					playerComponent->isBuilding = true;
				}
				else if (key2Pressed && currentBuild != BuildingType::TOWER) {
					tempBuildId = ef.createTower(*entityManager);
					currentBuild = BuildingType::TOWER;
					playerComponent->isBuilding = true;
				}
				else if (key3Pressed && currentBuild != BuildingType::MINE) {
					tempBuildId = ef.createMine(*entityManager);
					currentBuild = BuildingType::MINE;
					playerComponent->isBuilding = true;
				}
				else {
					currentBuild = BuildingType::NONE;
					playerComponent->isBuilding = false;
				}

				if (currentBuild != BuildingType::NONE) {
					auto appearance = entityManager->getComponent<AppearanceComponent>(tempBuildId);
					auto boundingBox = entityManager->getComponent<BoundingBoxComponent>(tempBuildId);
					auto position = entityManager->getComponent<PositionComponent>(tempBuildId);

					if (appearance != nullptr && boundingBox != nullptr && position != nullptr) {
						buildingId = entityManager->createEntity(*appearance, *boundingBox, *position, DynamicComponent());
						buildingColor = appearance->color;
						buildingScaleX = appearance->scaleX;
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
	}
}

void ECS::Systems::BuildSystem::placeCurrentBuild(Context &context, unsigned int playerId)
{
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
		appearance->scaleY = buildingScaleY;
		appearance->scaleZ = buildingScaleZ;

		auto shooting = entityManager->getComponent<ShootingComponent>(playerId);
		shooting->isShooting = false;

		if (canPlace && enoughResources) {
			if (context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {
				unsigned int tempId;
				//entityManager->removeEntity(buildingId);
				if (currentBuild == BuildingType::WALL) {
					//buildingId = ef.createWall(*entityManager);
					tempId = ef.createWall(*entityManager);
					inventory->greenResource -= wallRequirements;
				}
				else if (currentBuild == BuildingType::TOWER) {
					//buildingId = ef.createTower(*entityManager);
					tempId = ef.createWall(*entityManager);
					inventory->redResource -= towerRequirements;
				}
				else if (currentBuild == BuildingType::MINE) {
					//buildingId = ef.createMine(*entityManager);
					tempId = ef.createWall(*entityManager);
					inventory->blueResource -= mineRequirements;
				}
				//currentBuild = BuildingType::NONE;
				auto position = entityManager->getComponent<PositionComponent>(buildingId);
				if (position != nullptr) {
					position->x = posX;
					position->y = posY;
				}
				//buildingId = -1;
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
