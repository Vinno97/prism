#pragma once

#include <memory>
#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	class CreditsState : public State
	{
	public:
		CreditsState() = default;

		void onUpdate(Context &context) override;
		void onEnter(Context &context) override;

	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
	};
}

