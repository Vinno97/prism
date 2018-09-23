#include <math.h>

#include "ECS/Systems/MotionSystem.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"


ECS::Systems::MotionSystem::MotionSystem(EntityManager * entityManager) : System(entityManager) {}

ECS::Systems::MotionSystem::~MotionSystem()
= default;

void ECS::Systems::MotionSystem::update(Context context) {
	for (auto entity : entityManager->getAllEntities<VelocityComponent>()) {
		auto velocity = entity.component;

		// Drag gets calculated before the position gets moved. Otherwise it's not possible to easily move the position back later. 
		if (entityManager->hasComponent<DragComponent>(entity.id)) {
			auto drag = entityManager->getComponent<DragComponent>(entity.id);
			velocity->dx /= drag->force + 1;
			velocity->dy /= drag->force + 1;
			if (std::abs(velocity->dx) < 0.01) velocity->dx = 0;
			if (std::abs(velocity->dy) < 0.01) velocity->dy = 0;
		}

		if (entityManager->hasComponent<PositionComponent>(entity.id)) {
			auto position = entityManager->getComponent<PositionComponent>(entity.id);
			position->x += velocity->dx;
			position->y += velocity->dy;
		}
	}

}