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
#include <algorithm>


ECS::Systems::BuildSystem::BuildSystem(EntityManager &entityManager) : System(entityManager) { }

ECS::Systems::BuildSystem::~BuildSystem()
= default;


void ECS::Systems::BuildSystem::update(Context& context) {

	deltaTime += context.deltaTime;
	auto playerId = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0].id;



	if (deltaTime > pressTime) {
		auto inventory = entityManager->getComponent<InventoryComponent>(playerId);
		if (context.inputManager->isKeyPressed(Key::KEY_1)) {
			deltaTime = 0;
			if (!isBuilding) {
				if (true/*inventory->greenResource >= wallRequirements*/) {
					isBuilding = true;

					buildingId = ef.createWall(*entityManager);
					entityManager->addComponentToEntity(buildingId, DynamicComponent());
					buildingColor = entityManager->getComponent<AppearanceComponent>(buildingId)->color;
				}
				else {
					//TODO: niet genoeg resouces dus geluid ofzo?????
				}
			}
			else {
				isBuilding = false;
				entityManager->removeEntity(buildingId);
			}
		}
		else if (context.inputManager->isKeyPressed(Key::KEY_2)) {
			deltaTime = 0;
			if (!isBuilding) {
				if (true/*inventory->redResource >= towerRequirements*/) {
					isBuilding = true;

					buildingId = ef.createTower(*entityManager);
					entityManager->addComponentToEntity(buildingId, DynamicComponent());
					buildingColor = entityManager->getComponent<AppearanceComponent>(buildingId)->color;
				}
				else {
					//TODO: niet genoeg resouces dus geluid ofzo?????
				}
			}
			else {
				isBuilding = false;
				entityManager->removeEntity(buildingId);
			}
		}
		/*
		else if (context.inputManager->isKeyPressed(Key::KEY_3)) {
			deltaTime = 0;
			if (!isBuilding) {
				if (inventory->blueResource >= factoryRequirements) {
					isBuilding = true;

					//TODO :: Build Factory, heeft geen appearance???????/
					buildingId = ef.createEnemy(*entityManager);
					entityManager->addComponentToEntity(buildingId, DynamicComponent());
					buildingColor = entityManager->getComponent<AppearanceComponent>(buildingId)->color;
				}
				else {
					//TODO: niet genoeg resouces dus geluid ofzo?????
				}
			}
			else {
				isBuilding = false;
				entityManager->removeEntity(buildingId);
			}
		}*/
	}

	if (isBuilding) {
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(buildingId);
		bool canPlace = !boundingBoxComponent->didCollide;
		boundingBoxComponent->didCollide = false;

		auto appearance = entityManager->getComponent<AppearanceComponent>(buildingId);
		appearance->color = buildingColor;

		entityManager->getComponent<ShootingComponent>(playerId)->isShooting = false;

		if (canPlace) {
			if (isBuilding && context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {

				entityManager->removeComponentFromEntity<DynamicComponent>(buildingId);
				buildingId = -1;
				isBuilding = false;
			}
		}
		else {
			for (auto id : boundingBoxComponent->collidesWith) {
				auto &collider = (entityManager->getComponent<BoundingBoxComponent>(id)->collidesWith);
				//collider->erase(collider->begin(), collider->begin(), buildingId);
				collider.erase(std::remove(collider.begin(), collider.end(), buildingId), collider.end());
			}
			appearance->color = Math::Vector3f{ 1.0f, 0.5f, 0.5f };
		}
	}

	if (isBuilding) {
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

ECS::System * ECS::Systems::BuildSystem::clone()
{
	BuildSystem *nb = new BuildSystem(*entityManager);
	nb->buildingId = buildingId;
	nb->isBuilding = isBuilding;

	return nb;
}