#pragma once

#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"
#include "Util/AdvertisementSystem.h"

namespace States {
	class ResolutionMenuState : public State
	{
	public:
		ResolutionMenuState();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter(Context & context) override;
		void onLeave(Context & context) override;

		~ResolutionMenuState();

	private:
		Menu::MenuRenderer menuRenderer;
		bool exitBool = false;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;

		Renderer::Graphics::RenderDevice* renderDevice;
	};
}

