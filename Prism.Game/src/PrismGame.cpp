#include "PrismGame.h"

#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/RestockResourceSystem.h"

using namespace ECS;
using namespace ECS::Systems;
using namespace ECS::Components;

/// <summar>
/// creates new PrismGame object
/// </summary>
PrismGame::PrismGame() {
	entityManager = std::make_shared<EntityManager>();
	systemManager = std::make_shared<SystemManager>();
}

void PrismGame::onInit(Context & context)
{
	auto player = entityRegister.createPlayer(*entityManager);
	auto resourcePoint = entityRegister.createResourcePoint(*entityManager);
	auto enemy = entityRegister.createEnemy(*entityManager);

	for (int i = -4; i < 4; i++) {
		auto entity = i % 2 == 0 ? entityRegister.createTower(*entityManager) : entityRegister.createWall(*entityManager);
		auto position = entityManager->getComponent<PositionComponent>(entity);
		position->y = -1;
		position->x = i;
	}

	auto positions = entityManager->getAllEntitiesWithComponent<PositionComponent>();


	entityManager->getComponent<PositionComponent>(player)->y = 1;
	entityManager->getComponent<PositionComponent>(resourcePoint)->x = 1;
	entityManager->getComponent<PositionComponent>(enemy)->x = -1;

	registerSystems(context);
}

/// <summar>
/// register systems in system manager
/// </summary>
/// <param name="context">The context that is needed to register the systems</param>
void PrismGame::registerSystems(Context &context)
{
	MotionSystem motionSystem = MotionSystem(entityManager);
	RenderSystem renderSystem = RenderSystem(entityManager, context.window->width, context.window->height);
	KeyboardInputSystem inputSystem = KeyboardInputSystem(entityManager);
	RestockResourceSystem restockSystem = RestockResourceSystem(entityManager);
	systemManager->registerSystem(motionSystem);
	systemManager->registerSystem(renderSystem);
	systemManager->registerSystem(inputSystem);
	systemManager->registerSystem(restockSystem);
}

void PrismGame::onUpdate(Context &context)
{
	auto inputSystem = systemManager->getSystem<KeyboardInputSystem>();
	auto motionSystem = systemManager->getSystem<MotionSystem>();
	auto renderSystem = systemManager->getSystem<RenderSystem>();

	inputSystem->update(context);
	motionSystem->update(context);
	renderSystem->update(context);

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
