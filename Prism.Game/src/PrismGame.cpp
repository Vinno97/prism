#include "PrismGame.h"
#include "Math/Vector3f.h"

#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/RestockResourceSystem.h"
#include "ECS/Systems/AnimationSystem.h"

#include "World/WorldLoader.h"
#include "World/Assemblers/PrismEntityAssembler.h"

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
	auto scene = entityFactory.createScene(entityManager);

	auto sceneComponent = entityManager.getComponent<SceneComponent>(scene);

	sceneComponent->scene.ambientLightColor = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
	sceneComponent->scene.ambientLightStrength = 0.65f;
	sceneComponent->scene.sun.color = Math::Vector3f{ .30f, .30f, .30f };
	sceneComponent->scene.sun.direction = Math::Vector3f{ 25.f, 150.0f, 100.0f };

	World::LevelManager loader{ std::make_unique<PrismEntityAssembler>() };

	loader.load("levels/Sample World", entityManager);
	// Dit is hoe een wereld zou worden opgeslagen en weer ingeladen.
	//loader.load("saves/Sample Save", entityManager);
	//loader.save("saves/Sample Save", entityManager);

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
