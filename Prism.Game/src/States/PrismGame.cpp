#include "States/PrismGame.h"

#include "Math/Vector3f.h"
#include "StateMachine.h"
#include "States/PauseState.h"
#include "States/EndState.h"
#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/EnemyComponent.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
#include "ECS/Systems/EnemyPathFindingSystem.h"
#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Systems/AttackSystem.h"
#include "ECS/Systems/BumpSystem.h"
#include "ECS/Systems/CollisionSystem.h"
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
#include <functional>

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
		sceneComponent->scene.sun.color = Math::Vector3f{ .20f, .20f, .20f };
		sceneComponent->scene.sun.direction = Math::Vector3f{ 25.f, 150.0f, 100.0f };

		World::LevelManager loader{ std::make_unique<PrismEntityAssembler>() };

		loader.load("levels/Sample World", entityManager);
		// Dit is hoe een wereld zou worden opgeslagen en weer ingeladen.
		//loader.load("saves/Sample Save", entityManager);
		loader.save("saves/Sample Save", entityManager);

		loadAudio(context);

		registerSystems(context);

		context.stateMachine->addState<PauseState>(context);

		context.stateMachine->addState<EndState>(context);
		
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
			.registerSystem<1, EnemyPathFindingSystem>(entityManager, 10)

			//2
			.registerSystem<2, MotionSystem>(entityManager)
			.registerSystem<2, AnimationSystem>(entityManager)
			.registerSystem<2, AimingSystem>(entityManager)
			.registerSystem<2, ResourceGatherSystem>(entityManager)
			.registerSystem<2, EnemySpawnSystem>(entityManager)

			//3
			.registerSystem<3, CollisionSystem>(entityManager, context.window->width, context.window->height, 0, 0, 2)
			.registerSystem<3, ResourceBlobSystem>(entityManager)
			.registerSystem<3, ShootingSystem>(entityManager)

			//4
			.registerSystem<4, ProjectileAttackSystem>(entityManager)
			.registerSystem<4, AttackSystem>(entityManager)

			//5
			.registerSystem<5, RenderSystem>(entityManager, context.window->width, context.window->height)
			.registerSystem<5, BumpSystem>(entityManager);
	}



	void PrismGame::onUpdate(Context &context)
	{

		auto input = context.inputManager;
		if (menu.handleInput(*context.inputManager, context.window->width, context.window->height)) { 
			return; 
		}

		for (auto& systemList : systemManager.getAllSystems()) {
			for (auto& system : systemList.second) {
				system.second->update(context);
			}
		}
			
		
		std::cout << 1.0/context.deltaTime << std::endl;

		context.window->swapScreen();

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
	}

	void PrismGame::onEnter(Context &context) {
		context.audioManager->playMusic("Ambience");
	}
	void PrismGame::onLeave(Context &context) {
	}
}