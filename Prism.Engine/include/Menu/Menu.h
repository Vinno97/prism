#pragma once

#include "Menu/Control.h"
#include <vector>

namespace Menu {
	class Menu
	{
	public:
		Menu()=default;
		Menu(const Menu &other);
		std::vector<Control> controls;
	};
}