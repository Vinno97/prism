#include "Menu/MenuBuilder.h"
#include "Renderer/Renderable.h"
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

namespace Menu {
	MenuBuilder::MenuBuilder()
	{
		menu = Menu{};
	}

	void MenuBuilder::DrawInGameOverlay(int screenWidth, int screenHeight)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0.0f, screenWidth, screenHeight, 0.0f, 0.0f, 1.0f);

		glColor4ub(255, 255, 255, 255);

		glBegin(GL_QUADS);
		glVertex2i(50, 90);
		glVertex2i(100, 90);
		glVertex2i(100, 150);
		glVertex2i(50, 150);
		glEnd();
	}

	void MenuBuilder::addControl(int x, int y, int width, int height)
	{
		Control control{x, y, width, height};
		menu.controls.push_back(control);
	}
	Menu MenuBuilder::buildMenu()
	{
		return menu;
	}
}


