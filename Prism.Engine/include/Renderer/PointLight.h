#include "Math/Vector3f.h"

namespace Renderer {
	struct PointLight {
		Math::Vector3f position;
		Math::Vector3f color;
		float ambientIntensity;
		float diffuseIntensity;
		float constant;
		float linear;
		float exp;

		PointLight(Math::Vector3f position_, Math::Vector3f color_) : position{ position_ }, color{ color_ } {};
	};
}