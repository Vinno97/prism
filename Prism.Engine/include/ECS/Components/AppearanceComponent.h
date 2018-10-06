#pragma once
#include "Component.h"
#include "Renderer/Graphics/Models/Model.h"

using namespace Renderer::Graphics::Models;

namespace ECS {
	namespace Components {
		struct AppearanceComponent : Component {	
			Model* model;
			float posX;
			float posY;
			float posZ;
			float scaleX;
			float scaleY;
			float scaleZ;
			float rotX;
			float rotY;
			float rotZ;
		};
	}
}