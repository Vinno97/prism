#pragma once

#include "Menu/Control.h"
#include <vector>

namespace Menu {
	class Menu
	{
	public:
		Menu()=default;
		std::vector<Control> controls;
	};
}