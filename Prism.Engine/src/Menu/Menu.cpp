#include "Menu/Menu.h"
#include "..\..\include\Menu\Menu.h"
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

	Menu::~Menu()
	{
		cleanup();
	}

	void Menu::cleanup()
	{
		
	}
}