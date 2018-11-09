#pragma once
#include "Component.h"
#include "Renderer/Graphics/Models/Model.h"
#include "Math/Vector3f.h"

//using namespace Renderer::Graphics::Models;

namespace ECS {
	namespace Components {
		struct AppearanceComponent : Component {
			shared_ptr<Renderer::Graphics::Models::Model> model;
			float translationX = 0;
			float translationY = 0;
			float translationZ = 0;
			float scaleX = 1;
			float scaleY = 1;
			float scaleZ = 1;
			float rotationX = 0;
			float rotationY = 0;
			float rotationZ = 0;

			Math::Vector3f color{ 1.f, 1.f, 1.f };
		};
	}
}