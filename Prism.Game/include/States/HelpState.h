#pragma once

#include <memory>
#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	class HelpState : public State
	{
	public:
		HelpState() = default;

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;

	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
		Menu::Control* control;
		void swap();
		int count = 0;
		float maxcountDown = 1.0;
		float countDown = 0;
	};
}