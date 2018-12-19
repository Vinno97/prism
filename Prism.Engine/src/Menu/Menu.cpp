#include "Menu/Menu.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"

namespace Menu {
	bool Menu::handleInput(InputManager& input, int w, int h, Context context)
	{
		std::vector<int> pos = input.GetMousePoisiton();

		float x = (2.0f * pos[0]) / w - 1.0f;
		float y = 1.0f - (2.0f * pos[1]) / h;

		for (auto &control : controls) {
			if (control->position.x < x &&
				control->position.y < y &&
				control->position.x + control->size.x > x &&
				control->position.y + control->size.y > y) {
				if (input.isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT))
				{
					control->onClick();
					return true;
				}
				else if (!control->isActive && !hit) {
					control->onEnter(context);
				}
				return false;
			}
		}
		
		for (auto &control : controls) {
			if(control->isActive)
				control->onLeave(context);
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