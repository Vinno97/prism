#include <math.h>
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


ECS::Systems::BuildSystem::BuildSystem(EntityManager &entityManager) : System(entityManager) { }

ECS::Systems::BuildSystem::~BuildSystem()
= default;


void ECS::Systems::BuildSystem::update(Context& context) {
	deltaTime += context.deltaTime;
	
	//Player meegeven of contructor??
	auto playerId = entityManager->getAllEntitiesWithComponent<PlayerComponent>()[0].id;

	if (deltaTime > pressTime) {
		if (context.inputManager->isKeyPressed(Key::KEY_1)) {
			deltaTime = 0;
			if (!isBuilding) {
				isBuilding = true;
				
				buildingId = ef.createWall(*entityManager);
			}
			else {
				isBuilding = false;
				entityManager->removeEntity(buildingId);
			}
		}
	}

	if(isBuilding){
		auto boundingBoxComponent = entityManager->getComponent<BoundingBoxComponent>(buildingId);
		bool canPlace = !boundingBoxComponent->didCollide;

		//TODO :: CollisionSystem moet echt anders. komt hier altijd in omdat structurs geen velocity hebben
		if (canPlace) {
			if (isBuilding && context.inputManager->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT)) {
				entityManager->getComponent<ShootingComponent>(playerId)->isShooting = false;
				buildingId = -1;
				isBuilding = false;
			}
		}
		else {

		}

		auto entities = entityManager->getAllEntitiesWithComponent<MousePointerComponent>();
		if (entities.size() > 0) {
			auto entityId = entities[0].id;
			//auto component = entityManager->getComponent<PositionComponent>(entityId);
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