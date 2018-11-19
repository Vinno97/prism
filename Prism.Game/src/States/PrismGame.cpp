#include "States/PrismGame.h"
#include "Math/Vector3f.h"
#include "StateMachine.h"
#include "States/PauseState.h"
#include "ECS/Systems/EnemyPathFindingSystem.h"
#include "ECS/Components/PlayerComponent.h"

#include "World/WorldLoader.h"
#include "World/Assemblers/PrismEntityAssembler.h"

using namespace States;
using namespace ECS;
using namespace ECS::Components;
using namespace World::Assemblers;

/// <summary>
/// creates new PrismGame object
/// </summary>
PrismGame::PrismGame()
	= default;

void PrismGame::onInit(Context & context)
{
	auto floor = entityFactory.createFloor(entityManager);
	auto scene = entityFactory.createScene(entityManager);
	auto sceneComponent = entityManager.getComponent<SceneComponent>(scene);

	sceneComponent->scene.ambientLightColor = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
	sceneComponent->scene.ambientLightStrength = 0.95f;
	sceneComponent->scene.sun.color = Math::Vector3f{ .20f, .20f, .20f };
	sceneComponent->scene.sun.direction = Math::Vector3f{ 25.f, 150.0f, 100.0f };

	World::LevelManager loader{ std::make_unique<PrismEntityAssembler>() };

	loader.load("levels/Sample World", entityManager);
	// Dit is hoe een wereld zou worden opgeslagen en weer ingeladen.
	//loader.load("saves/Sample Save", entityManager);
	//loader.save("saves/Sample Save", entityManager);

	registerSystems(context);
	PauseState ps = PauseState();
	context.stateMachine->addState(ps);
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
	CollisionSystem collisionSystem = CollisionSystem(entityManager,200/* context.window->width*/,200/* context.window->height*/, 0, 0, 2);
	BumpSystem bumpSystem = BumpSystem(entityManager);
	AttackSystem attackSystem = AttackSystem(entityManager);
	EnemyPathFindingSystem enemyPathFindingSystem = EnemyPathFindingSystem(entityManager, 10.0);

	systemManager.registerSystem(motionSystem);
	systemManager.registerSystem(renderSystem);
	systemManager.registerSystem(inputSystem);
	systemManager.registerSystem(restockSystem);
	systemManager.registerSystem(animationSystem);
	systemManager.registerSystem(collisionSystem);
	systemManager.registerSystem(bumpSystem);
	systemManager.registerSystem(attackSystem);
	systemManager.registerSystem(enemyPathFindingSystem);
}

void PrismGame::onUpdate(Context &context)
{
	auto input = context.inputManager;
	if (input->isKeyPressed(Key::KEY_ESCAPE) && canPressEscape) {
		canPressEscape = false;
		context.stateMachine->setState<PauseState>();
	}

	if (!input->isKeyPressed(Key::KEY_ESCAPE)) {
		canPressEscape = true;
	}

	auto inputSystem = systemManager.getSystem<KeyboardInputSystem>();
	auto attackSystem = systemManager.getSystem<AttackSystem>();
	auto motionSystem = systemManager.getSystem<MotionSystem>();
	auto renderSystem = systemManager.getSystem<RenderSystem>();
	auto restockSystem = systemManager.getSystem<RestockResourceSystem>();
	auto animationSystem = systemManager.getSystem<AnimationSystem>();
	auto collisionSystem = systemManager.getSystem<CollisionSystem>();
	auto bumpSystem = systemManager.getSystem<BumpSystem>();
	auto enemyPathFindingSystem = systemManager.getSystem<EnemyPathFindingSystem>();

	inputSystem->update(context);
	
	restockSystem->update(context);
	enemyPathFindingSystem->update(context);
	motionSystem->update(context);
	
	collisionSystem->update(context);
	attackSystem->update(context);
	bumpSystem->update(context);
	animationSystem->update(context);
	renderSystem->update(context);
	
	for (auto &entity : entityManager.getAllEntitiesWithComponent<PlayerComponent>()) {
		auto velocity = entityManager.getComponent<VelocityComponent>(entity.id);
		auto position = entityManager.getComponent<PositionComponent>(entity.id);
		printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
	}

	context.window->swapScreen();
}
void PrismGame::onEnter() {
}
void PrismGame::onLeave() {
}