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
		EndState() = default;

		void onInit(Context &context) override;
		void onUpdate(Context &context) override;
		void onLeave(Context & context) override;

		~EndState();

	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
	};
}

