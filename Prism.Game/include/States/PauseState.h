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

		PauseState(const PauseState &obj);

		~PauseState();

	private:
		bool canPressEscape = false;
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		Menu::Menu menu;
	};
}

