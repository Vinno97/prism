#pragma once

#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	class MainMenuState : public State
	{
	public:
		MainMenuState();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter(Context & context) override;
		void onLeave() override;
		MainMenuState(const MainMenuState &obj);
		~MainMenuState();

	private:
		Menu::MenuRenderer menuRenderer;
		bool exitBool = false;
		Menu::MenuBuilder menuBuilder;
		Menu::Menu menu;
	};
}

