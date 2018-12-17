#include "Menu/TextRenderer.h"
#include "States/PrismGame.h"
#include "Math/Vector3f.h"
#include "StateMachine.h"
#include "States/PauseState.h"
#include "States/EndState.h"
#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/PlayerComponent.h"
#include "ECS/Components/ScoreComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Systems/EnemyPathFindingSystem.h"
#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/GameOverSystem.h"
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/EnemySpawnSystem.h"
#include "ECS/Systems/MousePointSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Systems/BumpSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CheatSystem.h"
#include "ECS/Systems/ScoreSystem.h"
#include "ECS/Systems/ResourceGatherSystem.h"
#include "ECS/Systems/ResourceBlobSystem.h"
#include "ECS/Systems/ShootingSystem.h"
#include "ECS/Systems/ProjectileAttackSystem.h"
#include "ECS/Systems/AimingSystem.h"
#include "World/WorldLoader.h"
#include "World/Assemblers/PrismEntityAssembler.h"
#include "ECS/Systems/HealthRegenerationSystem.h"
#include <functional>
#include "ECS/Systems/TowerAimingSystem.h"
#include "ECS/Systems/GeometryAnimationSystem.h"
#include "ECS/Systems/SetCurrentBuildSystem.h"
#include "ECS/Systems/MoveCurrentBuildSystem.h"
#include "ECS/Systems/PlaceCurrentBuildSystem.h"


namespace States {
	using namespace ECS;
	using namespace ECS::Components;
	using namespace World;
	using namespace World::Assemblers;

	void PrismGame::onInit(Context & context)
	{
		auto floor = entityFactory.getInstance().createFloor(entityManager);
		auto scene = entityFactory.getInstance().createScene(entityManager);
		auto camera = entityFactory.getInstance().createCamera(entityManager);
		auto mousePointer = entityFactory.getInstance().createCameraPointer(entityManager);
		auto sceneComponent = entityManager.getComponent<SceneComponent>(scene);

		sceneComponent->scene.ambientLightColor = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
		sceneComponent->scene.ambientLightStrength = 0.95f;
		sceneComponent->scene.sun.color = Math::Vector3f{ 1.f, 1.f, 1.f };
		sceneComponent->scene.sun.direction = Math::Vector3f{ 2, -1.0f, -.3f };

		World::LevelManager loader{ std::make_unique<PrismEntityAssembler>() };

		loader.load("levels/Level_1", entityManager);
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
		menuBuilder.addControl(-1, -0.97, 0.55, 0.20, "img/score.png");
		health = menuBuilder.addTextControl(-0.98, 0.89, 0.0012, Math::Vector3f{ 1.0f, 1.0f, 1.0f }, "100");
		blueResource = menuBuilder.addTextControl(0.65, 0.83, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		redResource = menuBuilder.addTextControl(0.65, 0.64, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		greenResource = menuBuilder.addTextControl(0.65, 0.45, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		survivedTime = menuBuilder.addTextControl(0.7, -0.95, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		fps = menuBuilder.addTextControl(0.725, 0.25, 0.0015, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "");
		score = menuBuilder.addTextControl(-0.98, -0.88, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
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
			.registerSystem<1, SetCurrentBuildSystem>(entityManager)

			//2
			.registerSystem<2, MotionSystem>(entityManager)
			.registerSystem<2, AnimationSystem>(entityManager)
			.registerSystem<2, AimingSystem>(entityManager)
			.registerSystem<2, ResourceGatherSystem>(entityManager)
			.registerSystem<2, EnemySpawnSystem>(entityManager)
			.registerSystem<2, MoveCurrentBuildSystem>(entityManager)

			//3
			.registerSystem<3, ResourceBlobSystem>(entityManager)
			.registerSystem<3, ShootingSystem>(entityManager)
			.registerSystem<3, TowerAimingSystem>(entityManager)
			.registerSystem<3, CollisionSystem>(entityManager, context.window->width, context.window->height, 0, 0, 2)
			

			//4
			.registerSystem<4, PlaceCurrentBuildSystem>(entityManager, 10, 10, 10,5)
			.registerSystem<4, ProjectileAttackSystem>(entityManager)
			.registerSystem<4, AttackSystem>(entityManager)
			.registerSystem<4, GeometryAnimationSystem>(entityManager)

			//5
			.registerSystem<5, BumpSystem>(entityManager)
			.registerSystem<5, GameOverSystem>(entityManager)
			.registerSystem<5, ScoreSystem>(entityManager)
			.registerSystem<5, RenderSystem>(entityManager, context.window->width, context.window->height)
			.registerSystem<5, HealthRegenerationSystem>(entityManager);
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
		float time;
		int totalScore;
		for (const auto& entity : entityManager.getAllEntitiesWithComponent<PlayerComponent>()) {
			playerHealth = entityManager.getComponent<HealthComponent>(entity.id)->currentHealth;
			
			auto scoreComponent = entityManager.getComponent<ScoreComponent>(entity.id);
			totalScore = scoreComponent->totalScore;
			//scoreComponent->survivedTime += context.deltaTime;
			time = scoreComponent->survivedTime;
		}

		redResource->text = std::to_string(static_cast<int>(inventory->redResource));
		blueResource->text = std::to_string(static_cast<int>(inventory->blueResource));
		greenResource->text = std::to_string(static_cast<int>(inventory->greenResource));
		health->text = "Health: " + std::to_string(playerHealth);
		score->text = "Score: " + std::to_string(totalScore);
		survivedTime->text = std::to_string(static_cast<int>(time)) + " seconds";

		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		context.window->swapScreen();

		if (menu->handleInput(*context.inputManager, context.window->width, context.window->height)) {
			//return;
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
		context.audioManager->addSound("Bullet", "Bullet.wav");
		context.audioManager->addSound("EnemyKill", "EnemyKill.wav");
		context.audioManager->addSound("Resource", "ResourceGathering.wav");
		context.audioManager->addSound("Heartbeat", "Heartbeat.wav");
	}

	void PrismGame::onEnter(Context &context) {
		auto scene = entityManager.getAllEntitiesWithComponent<SceneComponent>()[0];
		auto sceneCompontent = entityManager.getComponent<SceneComponent>(scene.id);
		if (isNightmareMode) {
			sceneCompontent->scene.ambientLightStrength = 0;
			sceneCompontent->scene.directionalLightStrength = 0;
		}
		else {
			sceneCompontent->scene.ambientLightStrength = 0.6f;
			sceneCompontent->scene.directionalLightStrength = 0.5f;
		}

		
		context.audioManager->playMusic("Ambience");
	}

	int PrismGame::Fps(Context &context)
	{
		return(floor(1.0 / context.deltaTime));
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
  
	void PrismGame::toggleNightmare(Context &context)
	{
		if (!isNightmareMode) {
			//TODO HAAL WEG
			//context.audioManager->playSound("NightmareOn", 0);
			isNightmareMode = true;
		}
		else {
			//TODO HAAL WEG
			//context.audioManager->playSound("NightmareOff", 0);
			isNightmareMode = false;
		}
	}
	bool PrismGame::isNightmare()
	{
		return isNightmareMode;
	}
}
