#pragma once
#include "Component.h"
#include "Renderer/Graphics/Models/Model.h"

using namespace Renderer::Graphics::Models;

namespace ECS {
	namespace Components {
		struct AppearanceComponent : Component {
			std::shared_ptr<Model> model;
			float translationX = 0;
			float translationY = 0;
			float translationZ = 0;
			float scaleX = 1;
			float scaleY = 1;
			float scaleZ = 1;
			float rotationX = 0;
			float rotationY = 0;
			float rotationZ = 0;
		};
	}
}