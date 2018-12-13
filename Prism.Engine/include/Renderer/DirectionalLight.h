#pragma once

#include "Math/Vector3f.h"

namespace Renderer
{
	class DirectionalLight
	{
	public:
		DirectionalLight() = default;
		Math::Vector3f direction;
		Math::Vector3f color;
	};
}
