#pragma once
#pragma once

#include "Component.h"
#include "Renderer/Camera.h"

namespace ECS
{
	namespace Components
	{
		struct CameraComponent : Component
		{
			Renderer::Camera camera;

			std::unique_ptr<Component> clone() override
			{
				auto component = std::make_unique<CameraComponent>();
				component->camera = camera;
				return component;
			}
		};
	}
}
