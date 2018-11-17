#include "Menu/Menu.h"

Menu::Menu::Menu(const Menu & other)
{
	for (auto const& control : other.controls) {
		controls.push_back(control);
	}
}
