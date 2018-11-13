#pragma once

#include "Menu/Menu.h"

namespace Menu {
	class MenuBuilder
	{
	public:
		MenuBuilder();
		void DrawInGameOverlay(int screenWidth, int screenHeight);
		void addControl(float x, float y, float width, float height, SDL_Window *window);
		Menu buildMenu();
	private:
		Menu menu;
	};
}