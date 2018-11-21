#pragma once

#include "Game.h"

#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "EntityFactory.h"
#include "State.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

#include "ECS/Components/SceneComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/DragComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

#include "ECS/Systems/MotionSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/MousePointSystem.h"

namespace States {

	class PrismGame : public State {
	public:
		PrismGame();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter() override;
		void onLeave() override;
	private:
		ECS::EntityManager entityManager;
		ECS::SystemManager systemManager;
		EntityFactory entityFactory;
		Menu::MenuBuilder menuBuilder;
		Menu::MenuRenderer menuRenderer;
		Menu::Menu menu;

		void registerSystems(Context &context);
		bool canPressEscape;
	};
} // namespace States
