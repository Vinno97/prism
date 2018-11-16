#pragma once
#pragma once

#include "Component.h"
#include "Renderer/Camera.h"

namespace ECS {
	namespace Components {
		struct CameraComponent : Component {
			Renderer::Camera camera;

			Component* Clone() override {
				CameraComponent* component = new CameraComponent();
				component->camera = camera;
				return component;
			}
		};
	}
}