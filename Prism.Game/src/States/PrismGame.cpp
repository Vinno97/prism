#include "States/PrismGame.h"
#include "States/PauseState.h"
#include "StateMachine.h"

#include "Math/Vector3f.h"
#include "ECS/Components/SceneComponent.h"

namespace States {
	/// <summar>
	/// creates new PrismGame object
	/// </summary>
	PrismGame::PrismGame() {
		entityManager = std::make_shared<EntityManager>();
		systemManager = std::make_shared<SystemManager>();
	}

	void PrismGame::onInit(Context & context)
	{
		createPlayer();
		registerSystems(context);
		PauseState ps = PauseState();
		context.stateMachine->addState(ps);
	}

	/// <summary>t
	/// create player entity
	/// </summary>
	void PrismGame::createPlayer() {
		// TODO: Deze functie moet later verplaatst worden naar een Factory of iets dergelijks.

		Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
		std::shared_ptr<Model> model = ml.loadModel("./res/varyingPlane.obj");

		VelocityComponent velocity;
		SceneComponent sceneComponent;
		sceneComponent.scene.ambientLightColor = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
		sceneComponent.scene.ambientLightStrength = 0.5f;

		sceneComponent.scene.sun.color = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
		sceneComponent.scene.sun.direction = Math::Vector3f{ 100.f, 50.0f, 100.0f };

		PositionComponent position;
		DragComponent drag;
		drag.force = 5.f;
		KeyboardInputComponent input;

		AppearanceComponent appearance;
		appearance.translationZ = 3;
		appearance.translationY = -3;
		appearance.scaleX = 1;
		appearance.scaleY = 1;
		appearance.scaleZ = 1;
		appearance.rotationY = 45;
		appearance.model = model;
		entityManager->createEntity(velocity, position, drag, input, appearance);
		entityManager->createEntity(sceneComponent);
	}

	/// <summar>
	/// register systems in system manager
	/// </summary>
	void PrismGame::registerSystems(Context &context)
	{
		MotionSystem motionSystem = MotionSystem(entityManager);
		RenderSystem renderSystem = RenderSystem(entityManager, context.window->width, context.window->height);
		KeyboardInputSystem inputSystem = KeyboardInputSystem(entityManager);
		systemManager->registerSystem(motionSystem);
		systemManager->registerSystem(renderSystem);
		systemManager->registerSystem(inputSystem);
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
		context.window->swapScreen();
	}
	void PrismGame::onEnter() {
	}
	void PrismGame::onLeave() {
	}

	PrismGame::~PrismGame()
		= default;
}