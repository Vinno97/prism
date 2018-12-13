#include "Menu/TextRenderer.h"
#include "States/PrismGame.h"
#include <iomanip>
#include <iostream>
#include "Math/Vector3f.h"
#include "StateMachine.h"
#include "States/PauseState.h"
#include "States/EndState.h"
#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/PointLightComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Systems/EnemyPathFindingSystem.h"
#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/GameOverSystem.h"
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/EnemySpawnSystem.h"
#include "ECS/Systems/MousePointSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Systems/BumpSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CheatSystem.h"
#include "ECS/Systems/ResourceGatherSystem.h"
#include "ECS/Systems/ResourceBlobSystem.h"
#include "ECS/Systems/ShootingSystem.h"
#include "ECS/Systems/ProjectileAttackSystem.h"
#include "ECS/Systems/AimingSystem.h"
#include "ECS/Systems/EnemySpawnSystem.h"
#include "ECS/Systems/MousePointSystem.h"
#include "World/WorldLoader.h"
#include "World/Assemblers/PrismEntityAssembler.h"
#include "ECS/Systems/MousePointSystem.h"
#include "ECS/Systems/EnemySpawnSystem.h"
#include "ECS/Systems/HealthRegenerationSystem.h"
#include "Renderer/PointLight.h"
#include <functional>
#include "ECS/Systems/TowerAimingSystem.h"
namespace States {
	using namespace ECS;
	using namespace ECS::Components;
	using namespace World;
	using namespace World::Assemblers;

	void PrismGame::onInit(Context & context)
	{
		auto floor = entityFactory.createFloor(entityManager);
		auto scene = entityFactory.createScene(entityManager);
		auto camera = entityFactory.createCamera(entityManager);
		auto mousePointer = entityFactory.createCameraPointer(entityManager);
		auto sceneComponent = entityManager.getComponent<SceneComponent>(scene);

		sceneComponent->scene.ambientLightColor = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
		sceneComponent->scene.ambientLightStrength = 0.95f;
		sceneComponent->scene.sun.color = Math::Vector3f{ 1.f, 1.f, 1.f };
		sceneComponent->scene.sun.direction = Math::Vector3f{ 2, -1.0f, -.3f };

		World::LevelManager loader{ std::make_unique<PrismEntityAssembler>() };

		loader.load("levels/motest", entityManager);
		// Dit is hoe een wereld zou worden opgeslagen en weer ingeladen.
		//loader.load("saves/Sample Save", entityManager);
		loader.save("saves/Sample Save", entityManager);

		loadAudio(context);
		registerSystems(context);
		
		if (!context.stateMachine->hasState<PauseState>()) {
			context.stateMachine->addState<PauseState>(context);
		}
		if (!context.stateMachine->hasState<EndState>()) {
			context.stateMachine->addState<EndState>(context);
		}

		menuBuilder.addControl(0.6, 0.35, 0.40, 0.65, "img/resources.png");
		menuBuilder.addControl(-1, 0.83, 0.4, 0.15, "img/healthbar.png");
		health = menuBuilder.addTextControl(-0.98, 0.89, 0.0012, Math::Vector3f{ 1.0f, 1.0f, 1.0f }, "100");
		blueResource = menuBuilder.addTextControl(0.65, 0.83, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		redResource = menuBuilder.addTextControl(0.65, 0.64, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		greenResource = menuBuilder.addTextControl(0.65, 0.45, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");



		fps = menuBuilder.addTextControl(0.83, 0.3, 0.0009, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "");

		menu = menuBuilder.buildMenu();

		
		std::function<void()> callback = [context, &canPress = canPressEscape]() mutable { canPress = false; context.stateMachine->setState<PauseState>(context); };
	}

	/// <summary>
	/// register systems in system manager
	/// </summary>
	/// <param name="context">The context that is needed to register the systems</param>
	void PrismGame::registerSystems(Context &context)
	{
			systemManager
			//1
			.registerSystem<1, KeyboardInputSystem>(entityManager)
			.registerSystem<1, MousePointSystem>(entityManager)
			.registerSystem<1, CheatSystem>(entityManager)
			.registerSystem<1, EnemyPathFindingSystem>(entityManager, 15)

			//2
			.registerSystem<2, MotionSystem>(entityManager)
			.registerSystem<2, AnimationSystem>(entityManager)
			.registerSystem<2, AimingSystem>(entityManager)
			.registerSystem<2, ResourceGatherSystem>(entityManager)
			.registerSystem<2, EnemySpawnSystem>(entityManager)

			//3
			.registerSystem<3, ResourceBlobSystem>(entityManager)
			.registerSystem<3, ShootingSystem>(entityManager)
			.registerSystem<3, TowerAimingSystem>(entityManager)
			.registerSystem<3, CollisionSystem>(entityManager, context.window->width, context.window->height, 0, 0, 2)

			//4
			.registerSystem<4, ProjectileAttackSystem>(entityManager)
			.registerSystem<4, AttackSystem>(entityManager)

			//5
			.registerSystem<5, BumpSystem>(entityManager)
			.registerSystem<5, RenderSystem>(entityManager, context.window->width, context.window->height)
			.registerSystem<5, HealthRegenerationSystem>(entityManager)
			.registerSystem<5, GameOverSystem>(entityManager);
	}

	void PrismGame::onUpdate(Context &context)
	{
		toggleFPS(context);
		auto input = context.inputManager;
	
		for (auto& systemList : systemManager.getAllSystems()) {
			for (auto& system : systemList.second) {
				system.second->update(context);
			}
		}
			
		auto inventory = entityManager.getAllEntitiesWithComponent<InventoryComponent>()[0].component;
		int playerHealth;
		for (const auto& entity : entityManager.getAllEntitiesWithComponent<PlayerComponent>()) {
			playerHealth = entityManager.getComponent<HealthComponent>(entity.id)->currentHealth;
		}

		redResource->text = std::to_string(static_cast<int>(inventory->redResource));
		blueResource->text = std::to_string(static_cast<int>(inventory->blueResource));
		greenResource->text = std::to_string(static_cast<int>(inventory->greenResource));
		health->text = "Health: " + std::to_string(playerHealth);

		menuRenderer.renderMenu(*menu, float(context.window->width) / float(context.window->height));
		context.window->swapScreen();

		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
			return;
		}


		if (!input->isKeyPressed(Key::KEY_ESCAPE)) {
			canPressEscape = true;
		}

		if (input->isKeyPressed(Key::KEY_ESCAPE) && canPressEscape) {
			canPressEscape = false;
			context.stateMachine->setState<PauseState>(context);
		}
	}

	void PrismGame::loadAudio(Context &context) const
	{
		context.audioManager->addMusic("Ambience", "Ambience.wav");
		context.audioManager->addMusic("MainMenu", "MainMenu.wav");
		context.audioManager->addSound("Bullet", "Bullet.wav");
		context.audioManager->addSound("EnemyKill", "EnemyKill.wav");
		context.audioManager->addSound("Resource", "ResourceGathering.wav");
		context.audioManager->addSound("Heartbeat", "Heartbeat.wav");
	}

	void PrismGame::onEnter(Context &context) {
		context.audioManager->playMusic("Ambience");
	}

	int PrismGame::Fps(Context &context)
	{
		double fps = 1.0 / context.deltaTime;
		return(floor(fps));
	}

	void PrismGame::toggleFPS(Context & context)
	{
		auto input = context.inputManager;
		if (!input->isKeyPressed(Key::KEY_F3)) {
			canPressF3 = true;
		}
		if (input->isKeyPressed(Key::KEY_F3) && !showFPS  && canPressF3) {
			canPressF3 = false;
			showFPS = true;
			fps->text = "FPS: " + std::to_string(Fps(context));
		}

		else if (input->isKeyPressed(Key::KEY_F3) && showFPS && canPressF3) {
			canPressF3 = false;
			showFPS = false;
			fps->text = "";
		}

		if (showFPS) {
			fps->text = "FPS: " + std::to_string(Fps(context));
		}
	}

	void PrismGame::onLeave(Context &context) {
	}
}