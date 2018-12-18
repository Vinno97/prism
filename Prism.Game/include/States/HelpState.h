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
		HelpState();

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onEnter(Context & context) override;
		void onLeave(Context & context) override;

		~HelpState();

	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
	};
}