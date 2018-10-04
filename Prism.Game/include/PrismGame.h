#pragma once

#include "Game.h"

#include "ECS/Entity.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"

#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/RenderSystem.h"

#include "ECS/Components/Component.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"
	
class PrismGame : public Game
{
public:
	PrismGame();
	void onUpdate(Context &context) override;
	void onEnter() override;
	void onLeave() override;
	~PrismGame();

private:
	ECS::EntityManager *entityManager;
	ECS::SystemManager *systemManager;

	void registerSystems();
	void createPlayer();
};
