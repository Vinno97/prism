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
		void onEnter(Context & context) override;
		void onLeave(Context & context) override;
		int totalscore;
		int time;
		int kills;
		int resourceRed;
		int resourceGreen;
		int resourceBlue;

		~EndState();
	private:
		Menu::MenuRenderer menuRenderer;
		Menu::MenuBuilder menuBuilder;
		std::unique_ptr<Menu::Menu> menu;

		Menu::TextControl* survivedTimeLabel;
		Menu::TextControl* scoreLabel;
		Menu::TextControl* killedEnemiesLabel;
		Menu::TextControl* redLabel;
		Menu::TextControl* greenLabel;
		Menu::TextControl* blueLabel;
		Menu::TextControl* statsLabel;

		Menu::TextControl* survivedTime;
		Menu::TextControl* score;
		Menu::TextControl* killedEnemies;
		Menu::TextControl* red;
		Menu::TextControl* green;
		Menu::TextControl* blue;

		void updateScores();
		float waitTime = .5f;
		float mouseWaitTime = .0f;
	};
}

