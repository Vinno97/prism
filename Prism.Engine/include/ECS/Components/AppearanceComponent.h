#pragma once
#include "Component.h"
#include "Renderer/Graphics/Models/Model.h"

using namespace Renderer::Graphics::Models;

namespace ECS {
	namespace Components {
		struct AppearanceComponent : Component {	
			Model* model;
			float x;
			float y;
			float z;
		};
	}
}