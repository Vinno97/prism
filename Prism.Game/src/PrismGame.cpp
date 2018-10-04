#include "PrismGame.h"



PrismGame::PrismGame() {
	createPlayer();
	registerSystems();
}

void PrismGame::createPlayer() {
	ECS::VelocityComponent velocity;
	ECS::PositionComponent position;
	ECS::DragComponent drag;
	drag.force = 0.1;
	entityManager.createEntity(velocity, position, drag);
}

void PrismGame::registerSystems() {
	ECS::MotionSystem motionSystem = ECS::MotionSystem(&entityManager);
	ECS::KeyboardInputSystem input = ECS::KeyboardInputSystem(&entityManager);
	systemManager.registerSystem(motionSystem);
	systemManager.registerSystem(input);
}

void PrismGame::onUpdate(Context context) {

	//auto input = systemManager.getSystem<ECS::KeyboardInputSystem>();
	//auto motion = systemManager.getSystem<ECS::MotionSystem>();
	//input->update(context);
	//motion->update(context);
	//for (auto &entity : entityManager.getAllEntitiesWithComponent<ECS::VelocityComponent>()) {
	//	auto velocity = entity.component;
	//	auto position = entityManager.getComponent<ECS::PositionComponent>(entity.id);
	//	printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
	//}
}
void PrismGame::onEnter() {
}
void PrismGame::onLeave() {
}

PrismGame::~PrismGame()
= default;
