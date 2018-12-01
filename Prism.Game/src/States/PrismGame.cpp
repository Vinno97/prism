#include "States/PrismGame.h"

#include "Math/Vector3f.h"
#include "StateMachine.h"
#include "States/PauseState.h"

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

namespace States {
	using namespace ECS;
	using namespace ECS::Components;
	using namespace World;
	using namespace World::Assemblers;

	void PrismGame::onInit(Context & context)
	{
		menuBuilder.addControl(-1.15, 0.88, 0.6, 0.07, "img/healthbar.png");
		menu = menuBuilder.buildMenu();
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
		EnemyPathFindingSystem enemyPathFindingSystem  = EnemyPathFindingSystem(entityManager, 10);
		AnimationSystem animationSystem = AnimationSystem(entityManager);
		CollisionSystem collisionSystem = CollisionSystem(entityManager, context.window->width, context.window->height, 0, 0, 2);
		ShootingSystem shootingSystem = ShootingSystem(entityManager);
		ProjectileAttackSystem projectileAttackSystem = ProjectileAttackSystem(entityManager);
		ResourceBlobSystem resourceBlobSystem = ResourceBlobSystem(entityManager);
		ResourceGatherSystem resourceGatherSystem = ResourceGatherSystem(entityManager);
		EnemySpawnSystem enemySpawnSystem = EnemySpawnSystem(entityManager);
		MousePointSystem pointSystem = MousePointSystem(entityManager);
		BumpSystem bumpSystem = BumpSystem(entityManager);
		AimingSystem aimSystem = AimingSystem(entityManager);
		AttackSystem attackSystem = AttackSystem(entityManager);

		systemManager.registerSystem(motionSystem);
		systemManager.registerSystem(renderSystem);
		systemManager.registerSystem(inputSystem);
		systemManager.registerSystem(enemyPathFindingSystem);

		systemManager.registerSystem(animationSystem);
		systemManager.registerSystem(collisionSystem);
		systemManager.registerSystem(shootingSystem);
		systemManager.registerSystem(projectileAttackSystem);
		systemManager.registerSystem(aimSystem);
		systemManager.registerSystem(bumpSystem);
		systemManager.registerSystem(resourceGatherSystem);
		systemManager.registerSystem(resourceBlobSystem);
		systemManager.registerSystem(enemySpawnSystem);
		systemManager.registerSystem(pointSystem);
		systemManager.registerSystem(attackSystem);
	}



	void PrismGame::onUpdate(Context &context)
	{
		std::cout << "FPS:   \t" << 1.0 / context.deltaTime << std::endl;
		context.deltaTime *= 2.5;

	    auto input = context.inputManager;

		auto inputSystem = systemManager.getSystem<KeyboardInputSystem>();
		auto enemyPathFindingSystem = systemManager.getSystem<EnemyPathFindingSystem>();
		auto motionSystem = systemManager.getSystem<MotionSystem>();
		auto collisionSystem = systemManager.getSystem<CollisionSystem>();
		auto renderSystem = systemManager.getSystem<RenderSystem>();
		auto animationSystem = systemManager.getSystem<AnimationSystem>();
		auto shootingSystem = systemManager.getSystem<ShootingSystem>();
		auto projectileAttackSystem = systemManager.getSystem<ProjectileAttackSystem>();
		auto attackSystem = systemManager.getSystem<AttackSystem>();
		auto bumpSystem = systemManager.getSystem<BumpSystem>();
		auto enemySpawnSystem = systemManager.getSystem<EnemySpawnSystem>();
		auto pointSystem = systemManager.getSystem<MousePointSystem>();
		auto aimSystem = systemManager.getSystem<AimingSystem>();
		auto resourceBlobSystem = systemManager.getSystem<ResourceBlobSystem>();
		auto resourceGatherSystem = systemManager.getSystem<ResourceGatherSystem>();

		inputSystem->update(context);
		enemyPathFindingSystem->update(context);
		
		collisionSystem->update(context);

		motionSystem->update(context);
		
		pointSystem->update(context);
		aimSystem->update(context);
		shootingSystem->update(context);
		projectileAttackSystem->update(context);
		//attackSystem->update(context);
		bumpSystem->update(context);

		animationSystem->update(context);
		resourceGatherSystem->update(context);
		resourceBlobSystem->update(context);
		enemySpawnSystem->update(context);
		renderSystem->update(context);

		
		
		auto enemies = entityManager.getAllEntitiesWithComponent<VelocityComponent>();
		std::cout << "Enemies:\t" << enemies.size() << std::endl;
		/*
		for (auto &entity : entityManager.getAllEntitiesWithComponent<VelocityComponent>()) {
			auto velocity = entity.component;
			auto position = entityManager.getComponent<PositionComponent>(entity.id);
			//printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
		}*/


		menuRenderer.renderMenu(menu, float(context.window->width) / float(context.window->height));
		context.window->swapScreen();

		if (input->isKeyPressed(Key::KEY_ESCAPE) && canPressEscape) {
			canPressEscape = false;
			context.stateMachine->setState<PauseState>();
		}

		if (!input->isKeyPressed(Key::KEY_ESCAPE)) {
			canPressEscape = true;
		}
	}
	void PrismGame::onEnter() {
	}
	void PrismGame::onLeave() {
	}
}


