#pragma once

#include <string>
#include "Math/Vector3f.h"

namespace Menu {
	class TextControl
	{
	public:
		TextControl(std::string text_) : text{ text_ } {};
		std::string text;

		Math::Vector3f position;
		Math::Vector3f size;
	};
}

