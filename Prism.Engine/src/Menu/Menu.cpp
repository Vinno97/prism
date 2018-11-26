#include "Menu/Menu.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"

namespace Menu {

	Menu::Menu(const Menu & other)
	{
		for (auto const& control : other.controls) {
			controls.push_back(control);
		}

		mesh = other.mesh;
	}

	Menu::Menu(Menu&& other)
	{
		controls = other.controls;
		mesh.swap(other.mesh);

		other.mesh = nullptr;
	}

	Menu & Menu::operator=(const Menu & other)
	{
		if (this != &other) {
			cleanup();

			for (auto const& control : other.controls) {
				controls.push_back(control);
			}
			mesh = other.mesh;
		}
		return *this;
	}

	Menu& Menu::operator=(Menu&& other)
	{
		if (this != &other) {
			cleanup();

			controls = other.controls;
			mesh.swap(other.mesh);

			other.mesh = nullptr;
		}
		return *this;
	}

	bool Menu::handleInput(InputManager& input, int w, int h)
	{
		std::vector<int> pos = input.GetMousePoisiton();

		float x = (2.0f * pos[0]) / w - 1.0f;
		float y = 1.0f - (2.0f * pos[1]) / h;

		for (auto &control : controls) {
			if (control.position.x < x &&
				control.position.y < y &&
				control.position.x + control.size.x > x &&
				control.position.y + control.size.y > y) {
				if (input.isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT))
				{
					control.onClick();
					return true;
				}
				else if (!control.isActive && !hit) {
					control.onEnter();
				}
				return false;
			}
		}
		
		for (auto &control : controls) {
			if(control.isActive)
				control.onLeave();
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