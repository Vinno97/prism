#pragma once

#include "Component.h"
#include "Renderer/Scene.h"

namespace ECS
{
	namespace Components
	{
		struct SceneComponent : Component
		{
			Renderer::Scene scene;

			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<SceneComponent>();
				component->scene = scene;
				return component;
			}
		};
	}
}
