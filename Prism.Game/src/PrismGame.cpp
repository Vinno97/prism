#include "PrismGame.h"
#include "Math/Vector3f.h"

using namespace ECS;
using namespace ECS::Components;

/// <summary>
/// creates new PrismGame object
/// </summary>
PrismGame::PrismGame()
= default;

void PrismGame::onInit(Context & context)
{
	auto player = entityFactory.createPlayer(entityManager);
	auto resourcePoint = entityFactory.createResourcePoint(entityManager);
	auto enemy = entityFactory.createEnemy(entityManager);
	auto scene = entityFactory.createScene(entityManager);

	for (int i = -4; i < 4; i++) {
		auto entity = i % 2 == 0 ? entityFactory.createTower(entityManager) : entityFactory.createWall(entityManager);
		auto position = entityManager.getComponent<PositionComponent>(entity);
		position->y = -1;
		position->x = i;
	}

	auto positions{ entityManager.getAllEntitiesWithComponent<PositionComponent>()};

	entityManager.getComponent<PositionComponent>(player)->y = 1;
	entityManager.getComponent<PositionComponent>(resourcePoint)->x = 1;
	entityManager.getComponent<PositionComponent>(enemy)->x = -1;
	
	auto sceneComponent = entityManager.getComponent<SceneComponent>(scene);

	sceneComponent->scene.ambientLightColor = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
	sceneComponent->scene.ambientLightStrength = 0.65f;
	sceneComponent->scene.sun.color = Math::Vector3f{ .30f, .30f, .30f };
	sceneComponent->scene.sun.direction = Math::Vector3f{ 25.f, 150.0f, 100.0f };

	registerSystems(context);
}

/// <summary>
/// register systems in system manager
/// </summary>
/// <param name="context">The context that is needed to register the systems</param>
void PrismGame::registerSystems(Context &context)
{
	MotionSystem motionSystem = MotionSystem(entityManager);
	RenderSystem renderSystem = RenderSystem(entityManager, context.window->width, context.window->height);
	KeyboardInputSystem inputSystem = KeyboardInputSystem(entityManager);
	RestockResourceSystem restockSystem = RestockResourceSystem(entityManager);
	AnimationSystem animationSystem = AnimationSystem(entityManager);
	
	systemManager.registerSystem(motionSystem);
	systemManager.registerSystem(renderSystem);
	systemManager.registerSystem(inputSystem);
	systemManager.registerSystem(restockSystem);
	systemManager.registerSystem(animationSystem);
}

void PrismGame::onUpdate(Context &context)
{
	auto inputSystem = systemManager.getSystem<KeyboardInputSystem>();
	auto motionSystem = systemManager.getSystem<MotionSystem>();
	auto renderSystem = systemManager.getSystem<RenderSystem>();
	auto restockSystem = systemManager.getSystem<RestockResourceSystem>();
	auto animationSystem = systemManager.getSystem<AnimationSystem>();

	inputSystem->update(context);
	restockSystem->update(context);
	motionSystem->update(context);
	animationSystem->update(context);
	renderSystem->update(context);

	for (auto &entity : entityManager.getAllEntitiesWithComponent<VelocityComponent>()) {
		auto velocity = entity.component;
		auto position = entityManager.getComponent<PositionComponent>(entity.id);
		printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
	}
}
void PrismGame::onEnter() {
}
void PrismGame::onLeave() {
}

PrismGame::~PrismGame()
= default;
