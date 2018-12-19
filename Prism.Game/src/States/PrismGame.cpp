#include "States/PrismGame.h"
#include "Menu/TextRenderer.h"
#include "Math/Vector3f.h"
#include "StateMachine.h"
#include "States/PauseState.h"
#include "States/EndState.h"
#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/EnemyComponent.h"
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

#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>


namespace States {
	using namespace ECS;
	using namespace ECS::Components;
	using namespace World;
	using namespace World::Assemblers;

	void PrismGame::onInit(Context & context)
	{
		auto floor = EntityFactory::getInstance().createFloor(entityManager);
		auto scene = EntityFactory::getInstance().createScene(entityManager);
		auto camera = EntityFactory::getInstance().createCamera(entityManager);
		auto mousePointer = EntityFactory::getInstance().createCameraPointer(entityManager);
		auto sceneComponent = entityManager.getComponent<SceneComponent>(scene);

		sceneComponent->scene.ambientLightColor = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
		sceneComponent->scene.ambientLightStrength = 0.95f;
		sceneComponent->scene.sun.color = Math::Vector3f{ 1.f, 1.f, 1.f };
		sceneComponent->scene.sun.direction = Math::Vector3f{ 2, -1.0f, -.3f };

		World::LevelManager loader{ std::make_unique<PrismEntityAssembler>() };

		loader.load(levelPath, entityManager);

		loadAudio(context);
		registerSystems(context);
		
		if (!context.stateMachine->hasState<PauseState>()) {
			context.stateMachine->addState<PauseState>();
		}
		if (!context.stateMachine->hasState<EndState>()) {
			context.stateMachine->addState<EndState>();
		}


		// Set highscore
		std::ifstream infile;
		infile.open("res/saves/scores.txt");
		std::vector<int> numbers;

		if (infile.is_open())
		{
			int num;
			while (infile >> num)
			{
				numbers.push_back(num);
			}
		}
		infile.close();

		if(!numbers.empty())
		{
			std::sort(numbers.begin(), numbers.end());
			std::reverse(numbers.begin(), numbers.end());
			currentHighscore = numbers[0];
		}


		health = menuBuilder.addTextControl(-0.95, 0.89, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "");
		resourceImage = menuBuilder.addImage(-0.97, 0.55, 0, 0, "img/resources.png");
		blueResource = menuBuilder.addTextControl(-0.92, 0.75, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "");
		greenResource = menuBuilder.addTextControl(-0.92, 0.66, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "");
		redResource = menuBuilder.addTextControl(-0.92, 0.57, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "");
		healthImage = menuBuilder.addImage(-0.98, 0.85, 0.6, 0.1, "img/healthbar.png");
		fps = menuBuilder.addTextControl(0.8, 0.9, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "");
		score = menuBuilder.addTextControl(-0.98, -0.95, 0.001, Math::Vector3f{ 0.1f, 0.1f, 0.1f }, "0");
		menu = menuBuilder.buildMenu();

		std::function<void()> callback = [context, &canPress = canPressEscape]() mutable { canPress = false; context.stateMachine->setState<PauseState>(); };
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
			.registerSystem<4, PlaceCurrentBuildSystem>(entityManager, 2, 25, 20, 5)
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
		auto input = context.inputManager;

		for (auto& systemList : systemManager.getAllSystems()) {
			for (auto& system : systemList.second) {
				system.second->update(context);
			}
		}
		
		int playerHealth;	
		float time;
		int totalScore;
		for (const auto& entity : entityManager.getAllEntitiesWithComponent<PlayerComponent>()) {
			playerHealth = entityManager.getComponent<HealthComponent>(entity.id)->currentHealth;
			
			auto scoreComponent = entityManager.getComponent<ScoreComponent>(entity.id);
			totalScore = scoreComponent->totalScore;
			time = scoreComponent->survivedTime;
		}

		float sizeHealth = ((float)playerHealth * 0.006);
		healthImage->size = Math::Vector3f{ sizeHealth, 0.1, 0};

		// Check if totalScore is >= 
		if (totalScore >= currentHighscore && currentHighscore != 0) {
			this->suspense_not_playing = false;
			context.audioManager->playMusic("AmbienceSuspense");
		}

		if (time > 120 && suspense_not_playing) {
			context.audioManager->playMusic("AmbienceTime");
            suspense_not_playing = false;
		}

	
		score->text = "Score: " + std::to_string(totalScore);
		menuRenderer.renderMenu(*menu, context.window->width, context.window->height);
		context.window->swapScreen();

		menu->handleInput(context);
		if (!input->isKeyPressed(Key::KEY_ESCAPE)) {
			canPressEscape = true;
		}

		if (input->isKeyPressed(Key::KEY_ESCAPE) && canPressEscape) {
			canPressEscape = false;
			context.stateMachine->setState<PauseState>();
		}
		changeTextColorNM();
		toggleFPS(context);
		toggleResources(context, playerHealth);
	}

	void PrismGame::loadAudio(Context &context) const
	{
		context.audioManager->addMusic("Ambience", "Ambience.wav");
		context.audioManager->addMusic("AmbienceSuspense", "Ambience_Suspense.wav");
		context.audioManager->addMusic("AmbienceTime", "Ambience_Time.wav");
		context.audioManager->addMusic("MainMenu", "MainMenu.wav");
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
		return static_cast<int>(floor(1.0 / context.deltaTime));
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

	void PrismGame::toggleResources(Context & context, int playerHealth)
	{
		auto inventory = entityManager.getAllEntitiesWithComponent<InventoryComponent>()[0].component;
		auto input = context.inputManager;

		if (input->isKeyPressed(Key::KEY_Q)) {
			health->text = "Health: " + std::to_string(playerHealth);
			resourceImage->size = Math::Vector3f{ 0.045, 0.25,  0 };
			redResource->text = std::to_string(static_cast<int>(inventory->redResource));
			blueResource->text = std::to_string(static_cast<int>(inventory->blueResource));
			greenResource->text = std::to_string(static_cast<int>(inventory->greenResource));
		}
		else {
			health->text = "";
			resourceImage->size = Math::Vector3f{ 0,0, 0 };
			redResource->text = "";
			blueResource->text = "";
			greenResource->text = "";
		}
	}

	void PrismGame::changeTextColorNM()
	{
		if (isNightmareMode) {
			score->colour = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
			redResource->colour = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
			blueResource->colour = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
			greenResource->colour = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
			fps->colour = Math::Vector3f{ 1.0f, 1.0f, 1.0f };
		}
	}

	void PrismGame::onLeave(Context &context) {
	}
  

	bool PrismGame::isNightmare()
	{
		return isNightmareMode;
	}

	void PrismGame::Save(std::string name)
	{
		World::LevelManager loader{ std::make_unique<PrismEntityAssembler>() };
		loader.save(name, entityManager);
	}
}
