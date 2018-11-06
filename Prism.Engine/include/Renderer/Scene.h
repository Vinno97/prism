#pragma once

#include "Math/Vector3f.h"

namespace Renderer {
	class Scene {
	public:
		Scene() = default;
		float ambientLightStrength;
		Math::Vector3f ambientLightColor;
		DirectionalLight testLight;
	};
}