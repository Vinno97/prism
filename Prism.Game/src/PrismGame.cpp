#include "PrismGame.h"


/// <summar>
/// creates new PrismGame object
/// </summary>
PrismGame::PrismGame() {
	entityManager = std::make_shared<EntityManager>();
	systemManager = std::make_shared<SystemManager>();
}

void PrismGame::onInit(Context & context)
{
	entityRegister.RegisterPlayer(entityManager);
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
	AttackSystem attackSystem = AttackSystem(entityManager);
	KeyboardInputSystem inputSystem = KeyboardInputSystem(entityManager);
	systemManager->registerSystem(motionSystem);
	systemManager->registerSystem(renderSystem);
	systemManager->registerSystem(inputSystem);
	systemManager->registerSystem(attackSystem);
}

void PrismGame::onUpdate(Context &context)
{
	auto inputSystem = systemManager->getSystem<KeyboardInputSystem>();
	auto motionSystem = systemManager->getSystem<MotionSystem>();
	auto renderSystem = systemManager->getSystem<RenderSystem>();
	auto attackSystem = systemManager->getSystem<AttackSystem>();

	inputSystem->update(context);
	motionSystem->update(context);
	renderSystem->update(context);
	attackSystem->update(context);

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
