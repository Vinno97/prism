#include "ECS/Systems/MoveCurrentBuildSystem.h"
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
using namespace Enums;

ECS::Systems::MoveCurrentBuildSystem::MoveCurrentBuildSystem(EntityManager &entityManager) : System(entityManager) {
}

ECS::Systems::MoveCurrentBuildSystem::~MoveCurrentBuildSystem()
= default;


void ECS::Systems::MoveCurrentBuildSystem::update(Context& context) {
	for (auto builder : entityManager->getAllEntitiesWithComponent<BuildComponent>()) {
		auto builderId = builder.id;
		auto &builderComponent = builder.component;

		if (builderComponent->isBuilding) {
			auto mouseComponents = entityManager->getAllEntitiesWithComponent<MousePointerComponent>();

			if (mouseComponents.size() > 0) {

				auto mouseId = mouseComponents[0].id;
				auto mousePosition = entityManager->getComponent<PositionComponent>(mouseId);

				if (mousePosition != nullptr) {
					auto buildingPosition = entityManager->getComponent<PositionComponent>(builderComponent->buildingId);
					auto builderPosition = entityManager->getComponent<PositionComponent>(builderId);

					buildingPosition->x = builderComponent->posX = std::ceil(mousePosition->x);
					buildingPosition->y = builderComponent->posY = std::ceil(mousePosition->y);








					std::cout << builderComponent->posX << " " << builderComponent->posY << std::endl;
					auto p = entityManager->getComponent<PositionComponent>(builderId);
					std::cout << p->x << " " << p->y << std::endl;
				}
			}
		}
	}
}
