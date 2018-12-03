#pragma once

#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	class CreditsState : public State
	{
	public:
		CreditsState();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter(Context & context) override;
		void onLeave(Context & context) override;

		CreditsState(const CreditsState &obj);

		~CreditsState();

	private:
		bool canPressEscape = false;
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		Menu::Menu menu;
	};
}

