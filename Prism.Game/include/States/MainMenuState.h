#pragma once

#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"
#include "Util/AdvertisementSystem.h"

namespace States {
	class MainMenuState : public State
	{
	public:
		MainMenuState();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter(Context & context) override;
		void onLeave(Context & context) override;

		~MainMenuState();

	private:
		Menu::MenuRenderer menuRenderer;
		bool exitBool = false;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
		float cooldown = 0.0f;
		float maxCooldown = 1.0f;
		Renderer::Graphics::RenderDevice* renderDevice;
	};
}

