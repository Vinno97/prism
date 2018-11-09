#pragma once

#include "Component.h"
#include "Renderer/Scene.h"

namespace ECS {
	namespace Components {
		struct SceneComponent: Component {
			Renderer::Scene scene;

			Component* Clone() { 
				SceneComponent* component = new SceneComponent();
				component->scene = scene;
				return component;
			}
		};
	}
}