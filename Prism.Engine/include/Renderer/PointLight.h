#include "Math/Vector3f.h"

#ifndef POINTLIGHT
#define POINTLIGHT

namespace Renderer {
	struct PointLight {
		Math::Vector3f position;
		Math::Vector3f color;
		float ambientIntensity = 0;
		float diffuseIntensity = 0;
		float constant = 1;
		float linear = 0;
		float exp = 1;

		PointLight(Math::Vector3f position_, Math::Vector3f color_) : position{ position_ }, color{ color_ } {};
		PointLight() = default;
	};
}

#endif