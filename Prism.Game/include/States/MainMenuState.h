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
		MainMenuState() = default;

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter(Context & context) override;

	private:
		Menu::MenuRenderer menuRenderer;
		bool exitBool = false;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
		Renderer::Graphics::RenderDevice* renderDevice;
		void loadMusic(Context &context);
	};
}

