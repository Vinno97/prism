#include "States/PrismGame.h"
#include "Math/Vector3f.h"
#include "StateMachine.h"
#include "States/PauseState.h"
#include "ECS/Systems/ResourceGatherSystem.h"
#include "ECS/Systems/ResourceBlobSystem.h"

namespace States {
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
		auto redResourcePoint = entityFactory.createResourcePoint(entityManager, Enums::ResourceType::RED, 1, 1);
		auto greenResourcePoint = entityFactory.createResourcePoint(entityManager, Enums::ResourceType::GREEN, 1, 1);
		auto blueResourcePoint = entityFactory.createResourcePoint(entityManager, Enums::ResourceType::BLUE, 1, 1);
		auto enemy = entityFactory.createEnemy(entityManager);
		auto scene = entityFactory.createScene(entityManager);

		for (int i = -4; i < 4; i++) {
			auto entity = i % 2 == 0 ? entityFactory.createTower(entityManager) : entityFactory.createWall(entityManager);
			auto position = entityManager.getComponent<PositionComponent>(entity);
			position->y = -1;
			position->x = i;
		}

		auto positions{ entityManager.getAllEntitiesWithComponent<PositionComponent>() };

		entityManager.getComponent<PositionComponent>(player)->y = 1;
		entityManager.getComponent<PositionComponent>(redResourcePoint)->x = 1;
		entityManager.getComponent<PositionComponent>(greenResourcePoint)->x = 2;
		entityManager.getComponent<PositionComponent>(blueResourcePoint)->x = 1;
		entityManager.getComponent<PositionComponent>(blueResourcePoint)->y = 1;
		entityManager.getComponent<PositionComponent>(enemy)->x = -1;

		auto sceneComponent = entityManager.getComponent<SceneComponent>(scene);

		sceneComponent->scene.ambientLightColor = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
		sceneComponent->scene.ambientLightStrength = 0.65f;
		sceneComponent->scene.sun.color = Math::Vector3f{ .30f, .30f, .30f };
		sceneComponent->scene.sun.direction = Math::Vector3f{ 25.f, 150.0f, 100.0f };

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
		AnimationSystem animationSystem = AnimationSystem(entityManager);
		ResourceGatherSystem resourceGatherSystem = ResourceGatherSystem(entityManager);
		ResourceBlobSystem resourceBlobSystem = ResourceBlobSystem(entityManager);

		systemManager.registerSystem(motionSystem);
		systemManager.registerSystem(renderSystem);
		systemManager.registerSystem(inputSystem);
		systemManager.registerSystem(animationSystem);
		systemManager.registerSystem(resourceGatherSystem);
		systemManager.registerSystem(resourceBlobSystem);
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
		auto motionSystem = systemManager.getSystem<MotionSystem>();
		auto renderSystem = systemManager.getSystem<RenderSystem>();
		auto animationSystem = systemManager.getSystem<AnimationSystem>();
		auto resourceGatherSystem = systemManager.getSystem<ResourceGatherSystem>();
		auto resourceBlobSystem = systemManager.getSystem<ResourceBlobSystem>();

		inputSystem->update(context);
		motionSystem->update(context);
		animationSystem->update(context);
		resourceGatherSystem->update(context);
		resourceBlobSystem->update(context);
		renderSystem->update(context);

		for (auto &entity : entityManager.getAllEntitiesWithComponent<VelocityComponent>()) {
			auto velocity = entity.component;
			auto position = entityManager.getComponent<PositionComponent>(entity.id);
			//printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
		}

		context.window->swapScreen();
	}
	void PrismGame::onEnter() {
	}
	void PrismGame::onLeave() {
	}
}