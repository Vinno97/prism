#include "Math/Vector3f.h"

struct PointLight {
	Math::Vector3f position;
	Math::Vector3f color;

	PointLight(Math::Vector3f position_, Math::Vector3f color_) : position{ position_ }, color{ color_ } {};
};