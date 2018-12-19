#include "Menu/Menu.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"

namespace Menu {

	bool Menu::handleInput(Context& context)
	{
		auto input = *context.inputManager;
		auto w = context.window->width;
		auto h = context.window->height;

		if (!input.isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT))
			isHandlingClicks = true;

		std::vector<int> pos = input.GetMousePoisiton();

		float x = (2.0f * pos[0]) / w - 1.0f;
		float y = 1.0f - (2.0f * pos[1]) / h;

		for (auto &control : controls) {
			if (control->position.x < x &&
				control->position.y < y &&
				control->position.x + control->size.x > x &&
				control->position.y + control->size.y > y) {
				if (input.isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT) && isHandlingClicks) {
					context.audioManager->playSound("ButtonClick", 0);
					control->onClick();
					return true;
				} else if (!control->isActive) {
					control->onEnter(context);
				}
			} else if (control -> isActive) {
				control->onLeave(context);
			}
		}

		return false;
	}

	Menu::~Menu()
	{
		cleanup();
	}

	void Menu::cleanup()
	{

	}
}