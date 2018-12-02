#pragma once

#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	class PauseState : public State
	{
	public:
		PauseState();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter() override;
		void onLeave() override;

		~PauseState();

	private:
		bool canPressEscape = false;
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
	};
}

