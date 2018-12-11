#pragma once

#include <string>
#include "Math/Vector3.h"

namespace Menu {
	class TextControl
	{
	public:
		TextControl(std::string text_) : text{ text_ } {};
		std::string text;
		Math::Vector3f colour;
		Math::Vector3f position;
		float scale;
	};
}

