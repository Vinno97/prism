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
#include "ECS/Components/AppearanceComponent.h"
#include "ECS/Components/KeyboardInputComponent.h"

#include "Renderer/Graphics/Loader/ModelLoader.h"

namespace States {
	class PrismGame : public Game
	{
	public:
		PrismGame();
		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter() override;
		void onLeave() override;
		~PrismGame();

	private:
		std::shared_ptr<EntityManager> entityManager;
		std::shared_ptr<SystemManager> systemManager;

		void registerSystems(Context &context);
		void createPlayer();
		bool canPressEscape = false;
	};
}
