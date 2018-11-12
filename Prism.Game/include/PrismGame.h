#pragma once

#include "Game.h"

#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "EntityFactory.h"

#include "EntityRegister.h"
#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/AttackSystem.h"

#include "ECS/Components/Component.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

#include "Renderer/Graphics/Loader/ModelLoader.h"


class PrismGame : public Game
{
public:
	PrismGame();
	void onInit(Context &context) override;
	void onUpdate(Context &context) override;
	void onEnter() override;
	void onLeave() override;

private:
	EntityManager entityManager;
	SystemManager systemManager;
	EntityFactory entityFactory;

	void registerSystems(Context &context);
};
