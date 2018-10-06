#include "PrismGame.h"



/// <summar>
/// creates new PrismGame object
/// </summary>
PrismGame::PrismGame() {
	entityManager = std::make_shared<EntityManager>();
	systemManager = std::make_shared<SystemManager>();
	createPlayer();
	registerSystems();
}

/// <summary>
/// create player entity
/// </summary>
void PrismGame::createPlayer() {
	VelocityComponent velocity;
	PositionComponent position;
	DragComponent drag;
	KeyboardInputComponent input;
	drag.force = 0.1;
	entityManager->createEntity(velocity, position, drag, input);
}

/// <summar>
/// register systems in system manager
/// </summary>
void PrismGame::registerSystems() 
{
	MotionSystem motionSystem = MotionSystem(entityManager);
	KeyboardInputSystem input = KeyboardInputSystem(entityManager);
	systemManager->registerSystem(motionSystem);
	systemManager->registerSystem(input);
}

void PrismGame::onUpdate(Context &context) 
{
	auto input = systemManager->getSystem<KeyboardInputSystem>();
	auto motion = systemManager->getSystem<MotionSystem>();

	input->update(context);
	motion->update(context);
	for (auto &entity : entityManager->getAllEntitiesWithComponent<VelocityComponent>()) {
		auto velocity = entity.component;
		auto position = entityManager->getComponent<PositionComponent>(entity.id);
		printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
	}
}
void PrismGame::onEnter() {
}
void PrismGame::onLeave() {
}

PrismGame::~PrismGame()
= default;
