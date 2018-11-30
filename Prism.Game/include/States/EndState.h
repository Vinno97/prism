#pragma once

#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	class EndState : public State
	{
	public:
		EndState();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter() override;
		void onLeave() override;

		EndState(const EndState &obj);

		~EndState();

	private:
		bool canPressEscape = false;
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		Menu::Menu menu;
	};
}

