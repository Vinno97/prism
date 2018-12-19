#pragma once

#include <memory>
#include "State.h"
#include "ECS/Systems/KeyboardInputSystem.h"
#include "Menu/MenuBuilder.h"
#include "Menu/Menu.h"
#include "Menu/MenuRenderer.h"

namespace States {
	class HighScoreState : public State
	{
	public:
		HighScoreState() = default;

		void onUpdate(Context &context) override;
		void onEnter(Context & context) override;

	private:
		void buildMenu(Context & context);
		std::vector<int> getHighScore();
		void showHighscore(std::vector<int> numbers, Context & context);
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;
	};
}