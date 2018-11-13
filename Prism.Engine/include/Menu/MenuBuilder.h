#pragma once

#include "Menu/Menu.h"

namespace Menu {
	class MenuBuilder
	{
	public:
		MenuBuilder();
		void DrawInGameOverlay(int screenWidth, int screenHeight);
		void addControl(float x, float y, float width, float height, const char *path);
		Menu buildMenu();
	private:
		Menu menu;
	};
}