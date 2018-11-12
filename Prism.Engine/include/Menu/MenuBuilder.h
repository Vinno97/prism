#pragma once

#include "Menu/Menu.h"

namespace Menu {
	class MenuBuilder
	{
	public:
		MenuBuilder();
		void DrawInGameOverlay(int screenWidth, int screenHeight);
		void addControl(int x, int y, int width, int height);
		Menu buildMenu();
	private:
		Menu menu;
	};
}