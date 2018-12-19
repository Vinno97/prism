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
		void onEnter(Context &context) override;
		void onUpdate(Context &context) override;
		void onLeave(Context & context) override;
		int totalscore{0};
		int time{0};
		int kills{0};
		int resourceRed{0};
		int resourceGreen{0};
		int resourceBlue{0};

	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;

		Menu::TextControl* survivedTimeLabel{};
		Menu::TextControl* scoreLabel{};
		Menu::TextControl* killedEnemiesLabel{};
		Menu::TextControl* redLabel{};
		Menu::TextControl* greenLabel{};
		Menu::TextControl* blueLabel{};
		Menu::TextControl* statsLabel{};

		Menu::TextControl* survivedTime{};
		Menu::TextControl* score{};
		Menu::TextControl* killedEnemies{};
		Menu::TextControl* red{};
		Menu::TextControl* green{};
		Menu::TextControl* blue{};

		void updateScores();
	};
}

